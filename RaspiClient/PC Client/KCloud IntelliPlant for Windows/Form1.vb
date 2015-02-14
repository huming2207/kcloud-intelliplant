Imports System.IO
Module modINI
    Private Declare Unicode Function WritePrivateProfileString Lib "kernel32" _
    Alias "WritePrivateProfileStringW" (ByVal lpApplicationName As String, _
    ByVal lpKeyName As String, ByVal lpString As String, _
    ByVal lpFileName As String) As Int32

    Private Declare Unicode Function GetPrivateProfileString Lib "kernel32" _
    Alias "GetPrivateProfileStringW" (ByVal lpApplicationName As String, _
    ByVal lpKeyName As String, ByVal lpDefault As String, _
    ByVal lpReturnedString As String, ByVal nSize As Int32, _
    ByVal lpFileName As String) As Int32

    Public Sub writeIni(ByVal iniFileName As String, ByVal Section As String, ByVal ParamName As String, ByVal ParamVal As String)
        Dim Result As Integer = WritePrivateProfileString(Section, ParamName, ParamVal, iniFileName)
    End Sub

    Public Function ReadIni(ByVal IniFileName As String, ByVal Section As String, ByVal ParamName As String, ByVal ParamDefault As String) As String
        Dim ParamVal As String = Space$(1024)
        Dim LenParamVal As Long = GetPrivateProfileString(Section, ParamName, ParamDefault, ParamVal, Len(ParamVal), IniFileName)
        ReadIni = Left$(ParamVal, LenParamVal)
    End Function
End Module


Public Class Form1
    Dim ssh As New ChilkatSsh()
    Dim sftp As New ChilkatSFtp
    Dim success As Boolean
    Dim channelNum As Long

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        RichTextBox4.AppendText(vbCrLf)
        RichTextBox4.AppendText(vbCrLf)
        RichTextBox4.AppendText(vbCrLf)
        RichTextBox4.AppendText("开始连接服务器......" + vbCrLf)
        RichTextBox4.AppendText("发送握手指令......" + vbCrLf)
        success = ssh.Connect(TextBox3.Text, 22)
        If (success <> True) Then
            RichTextBox4.AppendText(ssh.LastErrorText)
            Exit Sub
        End If
        ssh.IdleTimeoutMs = 5000
        RichTextBox4.AppendText("尝试认证密码......" + vbCrLf)
        success = ssh.AuthenticatePw(TextBox1.Text, TextBox2.Text)
        If (success <> True) Then
            RichTextBox4.AppendText(ssh.LastErrorText)
            Exit Sub
        End If

        channelNum = ssh.OpenSessionChannel()
        If (channelNum < 0) Then
            RichTextBox4.AppendText(ssh.LastErrorText)
            Exit Sub
        End If
        success = sftp.Connect(TextBox3.Text, 22)
        If (success <> True) Then
            RichTextBox4.AppendText(sftp.LastErrorText)
            Exit Sub
        End If
        sftp.IdleTimeoutMs = 5000
        RichTextBox4.AppendText("尝试认证密码......" + vbCrLf)
        sftp.AuthenticatePw(TextBox1.Text, TextBox2.Text)
        sftp.InitializeSftp()

        RichTextBox4.AppendText("连接成功，服务器：" + TextBox3.Text + vbCrLf)
        RichTextBox4.AppendText("正在下载配置文件......" + vbCrLf)
        File.Delete(Application.StartupPath() + "\Settings.conf")
        success = sftp.DownloadFileByName("/home/pi/Settings.conf", Application.StartupPath() + "\Settings.conf")
        If (success <> True) Then
            RichTextBox4.AppendText(sftp.LastErrorText)
            Exit Sub
        End If

        TextBox11.Text = ReadIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Key", TextBox11.Text)
        TextBox4.Text = ReadIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Humid", TextBox4.Text)
        TextBox5.Text = ReadIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Temp", TextBox5.Text)
        TextBox6.Text = ReadIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Baro", TextBox6.Text)
        TextBox7.Text = ReadIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "CPUTemp", TextBox7.Text)
        TextBox8.Text = ReadIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "CPUUsed", TextBox8.Text)
        TextBox9.Text = ReadIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "RAM", TextBox9.Text)
        RichTextBox4.AppendText("完成，您可以开始设置了！" + vbCrLf)
        MsgBox("成功联机，请进行下一步操作！", 0, "恭喜！")
        Button9.Enabled = True
        Button1.Enabled = False
    End Sub


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        success = ssh.UnlockComponent("SSHT34MB34N_710C9996584M")
        If (success <> True) Then
            RichTextBox4.AppendText(ssh.LastErrorText)
            Exit Sub
        End If
        RichTextBox4.AppendText("KCloud IntelliPlant 智慧植物客户端 版本1.0" + vbCrLf)
        RichTextBox4.AppendText("深圳科学高中 2015 By IT社 胡铭 Jackson Ming Hu <huming2207@gmail.com>" + vbCrLf)
        RichTextBox4.AppendText("本程序受GPLv2协议保护，严禁商用。" + vbCrLf)
    End Sub


    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        If ssh.IsConnected = 0 Then
            MsgBox("服务器未连接，保存失败！", 0, "连接错误")
            Exit Sub
        End If
        success = ssh.SendReqExec(channelNum, "sudo killall -9 python")
        If (success <> 1) Then
            MsgBox(ssh.LastErrorText)
            Exit Sub
        End If
    End Sub

    Private Sub Button9_Click(sender As Object, e As EventArgs) Handles Button9.Click
        ssh.Disconnect()
        MsgBox("成功结束连接！", 0, "恭喜！")
        Button9.Enabled = False
        Button1.Enabled = True
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        If ssh.IsConnected = 0 Then
            MsgBox("服务器未连接，保存失败！", 0, "连接错误")
            Exit Sub
        End If
        Button4.Enabled = False
        RichTextBox4.AppendText("写入设置中......" + vbCrLf)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Key", TextBox11.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Humid", TextBox4.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Temp", TextBox5.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Baro", TextBox6.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "CPUTemp", TextBox7.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "CPUUsed", TextBox8.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "RAM", TextBox9.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Camera", "ResolutionX", TextBox12.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Camera", "ResolutionY", TextBox13.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Camera", TextBox4.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Camera", "Rotate", TextBox5.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Camera", "Quality", TrackBar5.Value)
        writeIni(Application.StartupPath() + "\Settings.conf", "Camera", "EnableUpload", TextBox7.Text)

        RichTextBox4.AppendText("等待上传......" + vbCrLf)
        success = sftp.UploadFileByName("/home/pi/Settings.conf", Application.StartupPath() + "\Settings.conf")
        If (success <> 1) Then
            RichTextBox4.AppendText(sftp.LastErrorText)
            Exit Sub
        End If
        Button4.Enabled = True
        RichTextBox4.AppendText("完成，设置已生效！" + vbCrLf)
    End Sub

    Private Sub RichTextBox4_TextChanged(sender As Object, e As EventArgs) Handles RichTextBox4.TextChanged
        RichTextBox4.SelectionStart = RichTextBox4.Text.Length
        RichTextBox4.ScrollToCaret()

    End Sub

    Private Sub ComboBox10_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox10.SelectedIndexChanged

    End Sub

End Class

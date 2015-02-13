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
    Private Function UnicodeBytesToString(
    ByVal bytes() As Byte) As String
        Return System.Text.Encoding.UTF8.GetString(bytes)
    End Function



    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        success = ssh.Connect(TextBox3.Text, 22)
        If (success <> True) Then
            MsgBox(ssh.LastErrorText)
            Exit Sub
        End If
        ssh.IdleTimeoutMs = 5000
        success = ssh.AuthenticatePw(TextBox1.Text, TextBox2.Text)
        If (success <> True) Then
            MsgBox(ssh.LastErrorText)
            Exit Sub
        End If

        channelNum = ssh.OpenSessionChannel()
        If (channelNum < 0) Then
            MsgBox(ssh.LastErrorText)
            Exit Sub
        End If
        MsgBox("成功联机，请进行下一步操作！", 0, "恭喜！")
        Button9.Enabled = True
        Button1.Enabled = False
    End Sub


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        success = ssh.UnlockComponent("SSHT34MB34N_710C9996584M")
        If (success <> True) Then
            MsgBox(ssh.LastErrorText)
            Exit Sub
        End If
    End Sub

    Private Sub TabPage1_Click(sender As Object, e As EventArgs) Handles TabPage1.Click


    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        If ssh.IsConnected = 0 Then
            MsgBox("服务器未连接，保存失败！", 0, "连接错误")
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
        Button4.Enabled = False
        File.Delete(Application.StartupPath() + "\Settings.conf")
        System.IO.File.Create(Application.StartupPath() + "\Settings.conf")
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Key", TextBox11.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Humid", TextBox4.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Temp", TextBox5.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "Baro", TextBox6.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "CPUTemp", TextBox7.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "CPUUsed", TextBox8.Text)
        writeIni(Application.StartupPath() + "\Settings.conf", "Yeelink", "RAM", TextBox9.Text)

        sftp.Connect(TextBox3.Text, 22)
        sftp.AuthenticatePw(TextBox1.Text, TextBox2.Text)
        success = sftp.InitializeSftp()
        If (success <> 1) Then
            MsgBox(sftp.LastErrorText)
            Exit Sub
        End If

        success = sftp.UploadFileByName("/home/pi/Settings.conf", Application.StartupPath() + "\Settings.conf")
        If (success <> 1) Then
            MsgBox(sftp.LastErrorText)
            Exit Sub
        End If
        Button4.Enabled = True
    End Sub
End Class

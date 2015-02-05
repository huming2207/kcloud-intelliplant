Public Class Form2
    ' KCloud IntelliPlant , By Jackson Ming Hu , Shenzhen Highschool of Science
    ' Copyleft (C) 2015, Techonology Club of Shenzhen Highschool of Science
    Dim rx As String
    Dim rx2(10) As Integer


    Private Sub Button7_Click(sender As Object, e As EventArgs)
        AboutBox1.Show()
    End Sub


    Private Sub Button10_Click(sender As Object, e As EventArgs)
        Form3.Show()
    End Sub

    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Button11.Enabled = False
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            SerialPort1.PortName = ComboBox1.SelectedText
            SerialPort1.BaudRate = 9600 ' 串口波特率
            SerialPort1.DataBits = 8  ' 数据位
            SerialPort1.DtrEnable = False  ' 数据流控制（必须关掉不然会乱码）
            SerialPort1.StopBits = IO.Ports.StopBits.One '停止位
            SerialPort1.ReadTimeout = 100  '超时（有关读取的延时，防止出错的）
            SerialPort1.NewLine = vbCrLf '换行符设置
            SerialPort1.Open()
            Button1.Enabled = False
            Button11.Enabled = True
            MsgBox("串口已开启，届时" + "COM" + TextBox1.Text + "串口会被占用！", MsgBoxStyle.OkOnly, "信息")
        Catch ex As UnauthorizedAccessException      ' 如果发生无权限打开串口的错误……
            MsgBox("启动串口失败，串口被占用或USB转换器没有插入计算机", MsgBoxStyle.Critical, "错误")
        Catch ex As Exception
            MsgBox("串口不存在，USB转换器没有插入计算机", MsgBoxStyle.Critical, "错误")
        End Try
    End Sub

    Private Sub Button11_Click(sender As Object, e As EventArgs) Handles Button11.Click
        Try
            SerialPort1.Close()
            Button11.Enabled = False
            Button1.Enabled = True
            MsgBox("串口已关闭！", MsgBoxStyle.OkOnly, "信息")
        Catch ex As Exception
            MsgBox("串口无法关闭，出现未知错误", MsgBoxStyle.Critical, "错误")
        End Try
    End Sub
    Public Sub Serial_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Me.Invoke(New EventHandler(AddressOf Serial_Receiving)) ' 转接线程
    End Sub
    Private Sub Serial_Receiving(ByVal sender As Object, ByVal e As EventArgs)
        Dim i As Integer

        Try
            If SerialPort1.BytesToRead > 0 Then
                Threading.Thread.Sleep(100) ' 让线程延时一下
                Try
                    rx = SerialPort1.ReadLine() ' 赋上串口接收到的数据
                Catch ex As TimeoutException
                    rx = SerialPort1.ReadExisting()
                End Try
                For j As Integer = 1 To Len(rx)
                    If rx(j) = "," Then
                        i = i + 1
                    Else
                        rx2(i) = Int(rx(j))
                    End If
                Next
                rx = ""
                SerialPort1.DiscardInBuffer()
            End If
        Catch ex As Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub


    Private Sub TabControl1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles TabControl1.SelectedIndexChanged

    End Sub


    Private Sub PictureBox1_Click(sender As Object, e As EventArgs) Handles PictureBox1.Click

    End Sub
End Class


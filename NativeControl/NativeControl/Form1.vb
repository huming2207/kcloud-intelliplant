
Public Class Form1
    Dim rx As String
    Dim TextIncome() As String
    Dim SetStr1 As String
    Dim SetStr2 As String
    Dim SetStr3 As String
    Dim RatioStr As String
    Dim TimeStr As String


    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            SerialPort1.PortName = ComboBox1.Text
            SerialPort1.BaudRate = 9600 ' 串口波特率
            SerialPort1.DataBits = 8  ' 数据位
            SerialPort1.DtrEnable = False  ' 数据流控制（必须关掉不然会乱码）
            SerialPort1.StopBits = IO.Ports.StopBits.One '停止位
            SerialPort1.ReadTimeout = 100  '超时（有关读取的延时，防止出错的）
            SerialPort1.NewLine = vbCrLf '换行符设置
            SerialPort1.Open()
            Button2.Enabled = True
            Button1.Enabled = False
            MsgBox("串口已开启，届时" + ComboBox1.Text + "串口会被占用！", MsgBoxStyle.OkOnly, "信息")
        Catch ex As UnauthorizedAccessException      ' 如果发生无权限打开串口的错误……
            MsgBox("启动" + ComboBox1.Text + "串口失败，串口被占用或设备没有插入计算机", MsgBoxStyle.Critical, "错误")
        Catch ex As Exception
            MsgBox("串口" + ComboBox1.Text + "不存在，设备没有插入计算机", MsgBoxStyle.Critical, "错误")
        End Try
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Try
            SerialPort1.Close()
            Button2.Enabled = False
            Button1.Enabled = True
        Catch ex As Exception
            MsgBox("串口无法关闭，出现未知错误", MsgBoxStyle.Critical, "错误")
        End Try
    End Sub
    Private Sub Form_Closed(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Closed
        Try
            SerialPort1.Close()
            Button2.Enabled = False
            Button1.Enabled = True
        Catch ex As Exception
            MsgBox("串口无法关闭，出现未知错误", MsgBoxStyle.Critical, "错误")
        End Try
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        For Each sp As String In My.Computer.Ports.SerialPortNames
            ComboBox1.Items.Add(sp)
        Next
        ComboBox1.DropDownStyle = ComboBoxStyle.DropDownList

        Me.AutoScaleMode = AutoScaleMode.Dpi
        Me.AutoSize = True

    End Sub
    Public Sub Serial_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Me.Invoke(New EventHandler(AddressOf Serial_Receiving)) ' 转接线程
    End Sub
    Private Sub Serial_Receiving(ByVal sender As Object, ByVal e As EventArgs)
        ' Dim strIncoming As String
        Try
            If SerialPort1.BytesToRead > 0 Then
                Threading.Thread.Sleep(100) ' 让线程延时一下

                Try
                    rx = SerialPort1.ReadLine() ' 赋上串口接收到的数据
                Catch ex As TimeoutException
                    rx = SerialPort1.ReadExisting()
                End Try

                TextBox1.AppendText(rx + vbCrLf)
                TextIncome = Split(rx, ",")
                Select Case TextIncome(0)
                    Case "1"
                        Label3.Text = TextIncome(3) + "℃"
                        Label4.Text = TextIncome(2) + "%"
                        Label6.Text = TextIncome(4) + "Pa"
                    Case "2"
                        MsgBox("预设灌溉指令执行中" + vbCrLf + "指令时间" + TextIncome(1) + ":" + TextIncome(2) + "  编号#" + TextIncome(3))
                End Select


                SerialPort1.DiscardInBuffer()
                rx = ""

            End If
        Catch ex As Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub
    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        SerialPort1.WriteLine("5,1")
        MsgBox("水泵已启动，注意安全！")
    End Sub
    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        SerialPort1.WriteLine("5,-1")
        MsgBox("水泵已关闭，注意安全！")
    End Sub
End Class

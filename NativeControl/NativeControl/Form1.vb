Public Class Form1
    Dim rx As String
    Dim TextIncome() As String
    Private Sub ComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox1.SelectedIndexChanged

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            SerialPort1.PortName = ComboBox1.Text
            SerialPort1.BaudRate = 38400 ' 串口波特率
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
                        Label3.Text = TextIncome(3)
                        Label4.Text = TextIncome(2)
                        Label6.Text = TextIncome(4)
                    Case "2"
                        MsgBox("预设灌溉指令执行中" + vbCrLf + "指令时间" + TextIncome(1) + ":" + TextIncome(2) + "  编号#" + TextIncome(3))
                End Select


                SerialPort1.DiscardInBuffer()
            End If
        Catch ex As Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub

    Private Sub TextBox1_TextChanged(sender As Object, e As EventArgs) Handles TextBox1.TextChanged

    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click

    End Sub
End Class

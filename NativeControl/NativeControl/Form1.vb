Public Class Form1

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

 
    Private Sub Button8_Click(sender As Object, e As EventArgs) Handles Button8.Click

    End Sub
End Class

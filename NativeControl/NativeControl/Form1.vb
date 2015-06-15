
Public Class Form1
    Dim rx As String
    Dim TextIncome() As String
    Dim SetStr1 As String
    Dim SetStr2 As String
    Dim SetStr3 As String
    Dim RatioStr As String
    Dim TimeStr As String
    Dim SetFlag As Integer


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
            GroupBox3.Enabled = True
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

        GroupBox3.Enabled = False
        ComboBox8.Enabled = False
        ComboBox9.Enabled = False
        ComboBox10.Enabled = False
        CheckBox3.Enabled = False
        TextBox5.Enabled = False
        ComboBox5.Enabled = False
        ComboBox6.Enabled = False
        ComboBox7.Enabled = False
        CheckBox2.Enabled = False
        ComboBox2.Enabled = False
        ComboBox3.Enabled = False
        ComboBox4.Enabled = False
        CheckBox1.Enabled = False
        TextBox3.Enabled = False

    End Sub
    Public Sub Serial_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Me.Invoke(New EventHandler(AddressOf Serial_Receiving)) ' 转接线程
    End Sub
    Private Sub Serial_Receiving(ByVal sender As Object, ByVal e As EventArgs)
        ' Dim strIncoming As String
        Try
            Try
                Select Case SetFlag
                    Case 1
                        SetFlag = 0
                        SerialPort1.Write("5,1")
                        Threading.Thread.Sleep(100)
                    Case 2
                        SetFlag = 0
                        SerialPort1.Write("5,-1")
                        Threading.Thread.Sleep(100)
                    Case 3
                        SetFlag = 0
                        SerialPort1.Write(SetStr1)
                        TextBox2.AppendText(SetStr1 + vbCrLf)
                        Threading.Thread.Sleep(100)
                        SerialPort1.Write(SetStr2)
                        TextBox2.AppendText(SetStr2 + vbCrLf)
                        Threading.Thread.Sleep(100)
                        SerialPort1.Write(SetStr3)
                        TextBox2.AppendText(SetStr3 + vbCrLf)
                        Threading.Thread.Sleep(100)
                        SetStr1 = ""
                        SetStr2 = ""
                        SetStr3 = ""
                    Case 4
                        SetFlag = 0
                        SerialPort1.Write(RatioStr)
                        Threading.Thread.Sleep(100)
                        RatioStr = ""
                    Case 5
                        SetFlag = 0
                        SerialPort1.Write(TimeStr)
                        Threading.Thread.Sleep(100)
                        TimeStr = ""
                    Case 6
                        SetFlag = 0
                        SerialPort1.Write("8,1")
                        Threading.Thread.Sleep(100)
                    Case Else
                        ' 啥也不用做，等着下一个循环即可
                End Select
                ' SerialPort1.DiscardOutBuffer()   '别忘了还得清理一下缓存！(不过好像并不需要这东西)
            Catch ex1 As Exception
                MessageBox.Show(ex1.Message)
            End Try

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
        SetFlag = 1
        MsgBox("水泵已启动，注意安全！")
    End Sub
    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        SetFlag = 2
        MsgBox("水泵已关闭！")
    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        If CheckBox5.Checked = True Then
            SetStr1 = "2," + ComboBox2.Text + "," + ComboBox3.Text + "," + ComboBox4.Text + "," + TextBox3.Text + ",1," + Convert.ToString(Convert.ToInt32(CheckBox1.Checked))
        Else
            SetStr1 = "2," + ComboBox2.Text + "," + ComboBox3.Text + "," + ComboBox4.Text + "," + TextBox3.Text + ",0," + Convert.ToString(Convert.ToInt32(CheckBox1.Checked))
        End If

        If CheckBox6.Checked = True Then
            SetStr1 = "3," + ComboBox7.Text + "," + ComboBox6.Text + "," + ComboBox5.Text + "," + TextBox4.Text + ",1," + Convert.ToString(Convert.ToInt32(CheckBox2.Checked))
        Else
            SetStr1 = "3," + ComboBox7.Text + "," + ComboBox6.Text + "," + ComboBox5.Text + "," + TextBox4.Text + ",0," + Convert.ToString(Convert.ToInt32(CheckBox2.Checked))
        End If

        If CheckBox7.Checked = True Then
            SetStr1 = "4," + ComboBox10.Text + "," + ComboBox9.Text + "," + ComboBox8.Text + "," + TextBox5.Text + ",1," + Convert.ToString(Convert.ToInt32(CheckBox3.Checked))
        Else
            SetStr1 = "4," + ComboBox10.Text + "," + ComboBox9.Text + "," + ComboBox8.Text + "," + TextBox5.Text + ",0," + Convert.ToString(Convert.ToInt32(CheckBox3.Checked))
        End If
        SetFlag = 3
        MsgBox("命令已发送！", MsgBoxStyle.Information, "执行完毕！")
    End Sub

    Private Sub CheckBox5_CheckedChanged(sender As Object, e As EventArgs) Handles CheckBox5.CheckedChanged
        If CheckBox5.Checked = False Then
            ComboBox2.Enabled = False
            ComboBox3.Enabled = False
            ComboBox4.Enabled = False
            CheckBox1.Enabled = False
            TextBox3.Enabled = False
        Else
            ComboBox2.Enabled = True
            ComboBox3.Enabled = True
            ComboBox4.Enabled = True
            CheckBox1.Enabled = True
            TextBox3.Enabled = True
        End If
    End Sub

    Private Sub CheckBox6_CheckedChanged(sender As Object, e As EventArgs) Handles CheckBox6.CheckedChanged
        If CheckBox6.Checked = False Then
            ComboBox5.Enabled = False
            ComboBox6.Enabled = False
            ComboBox7.Enabled = False
            CheckBox2.Enabled = False
            TextBox4.Enabled = False
        Else
            ComboBox5.Enabled = True
            ComboBox6.Enabled = True
            ComboBox7.Enabled = True
            CheckBox2.Enabled = True
            TextBox4.Enabled = True
        End If
    End Sub

    Private Sub CheckBox7_CheckedChanged(sender As Object, e As EventArgs) Handles CheckBox7.CheckedChanged
        If CheckBox7.Checked = False Then
            ComboBox8.Enabled = False
            ComboBox9.Enabled = False
            ComboBox10.Enabled = False
            CheckBox3.Enabled = False
            TextBox5.Enabled = False
        Else
            ComboBox8.Enabled = True
            ComboBox9.Enabled = True
            ComboBox10.Enabled = True
            CheckBox3.Enabled = True
            TextBox5.Enabled = True
        End If
    End Sub

    Private Sub Button8_Click(sender As Object, e As EventArgs) Handles Button8.Click

    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        SetFlag = 6
        MsgBox("设备即将重启！")
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click


        TimeStr = "1," + Convert.ToString(Now.Year) + "," + Convert.ToString(Now.Month) + "," + Convert.ToString(Now.Day) + "," + Convert.ToString(Now.Hour) + "," + Convert.ToString(Now.Minute) + "," + Convert.ToString(Now.Second)
        SetFlag = 5
        MsgBox("时间已发送！" + vbCrLf + "现在时间（调试内容）：" + vbCrLf + TimeStr)
    End Sub

    Private Sub Button9_Click(sender As Object, e As EventArgs) Handles Button9.Click
        Form2.ShowDialog()
    End Sub
End Class

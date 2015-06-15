Public Class Form2

    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Label2.Text = Convert.ToString(Reflection.Assembly.GetExecutingAssembly().GetName().Version)
    End Sub
End Class
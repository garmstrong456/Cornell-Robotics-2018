using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RGB_Color_Mixer
{
    public partial class RGBmixer : Form
    {
        byte red = 0;
        byte green = 0;
        byte blue = 0;

        public RGBmixer()
        {
            InitializeComponent();
            setRGB();
        }
        
        public void setRGB()
        {
            
            red = Convert.ToByte(trackBarRed.Value);
            green = Convert.ToByte(trackBarGreen.Value);
            blue = Convert.ToByte(trackBarBlue.Value);

            labelR.Text = red.ToString();
            labelG.Text = green.ToString();
            labelB.Text = blue.ToString();

            txtHexValue.Text = "0x" + showHex(red, green, blue).PadLeft(4,'0');

            RGBcolorDialog.BackColor = Color.FromArgb(red, green, blue);
        }

        private void trackBarRed_Scroll(object sender, EventArgs e)
        {
            setRGB();
        }

        private void trackBarGreen_Scroll(object sender, EventArgs e)
        {
            setRGB();
        }

        private void trackBarBlue_Scroll(object sender, EventArgs e)
        {
            setRGB();
        }

        public string showHex(byte r, byte b, byte g)
        {
            int result = ((r / 8) << 11) | ((b / 4) << 5) | (g / 8);
            return Convert.ToInt32(result).ToString("X");
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}

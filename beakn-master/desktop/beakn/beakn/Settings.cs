using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;

namespace beakn
{
    public partial class Settings : Form
    {
        public Settings()
        {
            InitializeComponent();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
           Config.Protocol=comboBox1.SelectedItem.ToString();
            Properties.Settings.Default.AccessToken = accessTokenTextbox.Text;
            Properties.Settings.Default.DeviceId = deviceIdTextbox.Text;
            Properties.Settings.Default.Save();
            this.Close();
        }

        private void sparkLinkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start(sparkLinkLabel.Text);
        }
        private static string GetSetting(string key)
        {
            return ConfigurationManager.AppSettings[key];
        }

        private static void SetSetting(string key, string value)
        {
            Configuration configuration =
                ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            configuration.AppSettings.Settings[key].Value = value;
            configuration.Save(ConfigurationSaveMode.Full, true);
            ConfigurationManager.RefreshSection("appSettings");
        }
    }
}

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Threading;
namespace stm32timer
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>

    public abstract class ModelBase : INotifyPropertyChanged
    {
        SynchronizationContext context;
        public ModelBase(SynchronizationContext _context)
        {
            context = _context;
            OnPropertyChanged = propertyName =>
            {
                PropertyChangedEventHandler handler = this.PropertyChanged;
                if (handler != null)
                {
                    context.Post(t => handler(this, new PropertyChangedEventArgs((string)t)), propertyName);
                }
            };
        }
        public ModelBase()
        {
            OnPropertyChanged = propertyName =>
            {
                PropertyChangedEventHandler handler = this.PropertyChanged;
                if (handler != null)
                {
                    handler(this, new PropertyChangedEventArgs(propertyName));
                }
            };
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected Action<string> OnPropertyChanged;
    }
    public class ProxyIP : ModelBase
    {
    #if true
        #region 多线程中异步回调触发

        string _Index;
        public string Index
        {
            get { return _Index; }
            set
            {
                if (_Index != value)
                {
                    _Index = value;
                  //  OnPropertyChanged("Index");
                }
            }
        }
        string _integers;
        public string integers
        {
            get { return _integers; }
            set
            {
                if (_integers != value)
                {
                    _integers = value;
                  //  OnPropertyChanged("integers");
                }
            }
        }
        string _decimals;
        public string decimals
        {
            get { return _decimals; }
            set
            {
                if (_decimals != value)
                {
                    _decimals = value;
                  //  OnPropertyChanged("decimals");
                }
            }
        }
       
       
      
        string _Speed = "未知";
        public string Speed
        {
            get { return _Speed; }
            set
            {
                if (_Speed != value)
                {
                    _Speed = value;
                 //   OnPropertyChanged("Speed");
                }
            }
        }
        string _reload = "未知";
        public string reload
        {
            get { return _reload; }
            set
            {
                if (_reload != value)
                {
                    _reload = value;
                   // OnPropertyChanged("reload");
                }
            }
        }
        string _prescale = "未知";
        public string prescale
        {
            get { return _prescale; }
            set
            {
                if (_prescale != value)
                {
                    _prescale = value;
                   // OnPropertyChanged("prescale");
                }
            }
        }
        string _deviation = "未知";
        public string deviation
        {
            get { return _deviation; }
            set
            {
                if (_deviation != value)
                {
                    _deviation = value;
                    // OnPropertyChanged("deviation");
                }
            }
        }
        #endregion
#else
        #region 非异步回调
        //public string IP { get; set; }
        //public string Port { get; set; }
        //public string Index { get; set; }
        //private string _Place = "未知";
        //public string Place
        //{
        //    get { return _Place; }
        //    set { _Place = value; }
        //}
        //private string _Anonymity = "未知";
        //public string Anonymity
        //{
        //    get { return _Anonymity; }
        //    set { _Anonymity = value; }
        //}
        //private string _Speed = "未知";
        //public string Speed
        //{
        //    get { return _Speed; }
        //    set { _Speed = value; }
        //}
        #endregion
#endif
    }
//以上代码实现多线程
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }
        public class SettingValue
        {
            public int timeout;//TimeOut时间
            public int threadnum;//线程数
        }

        List<ProxyIP> myList = new List<ProxyIP>();

        int sysclk = 72;
        int accuracy_value = 0;//精度
        int voice_clk = 44100;
        int count = 0;
        int index = 0;
        public void checkvalue() {

            double tm = 0;
            double tm0 = 0;
            int j;
            int presc;
            int rlod;
            int dvt;
                int dec;    //小数
                int intg;   //整数
                tm0 = (1000000000 / voice_clk);
                sample.Text = tm0.ToString();
                for (int i = 1; i < sysclk; i++)
                {

                    j = (sysclk * 1000 / i) ;

                    tm = (sysclk*(1000000*1000 / voice_clk)) / (j / 1000);
                    //tm = (1000000000 / voice_clk) * i;
                    intg = (int)tm /1000;
                    dec = (int)tm % 1000;

                    if (dec < accuracy_value)
                    {
                        ProxyIP pp = new ProxyIP();
                        pp.decimals = "0";
                        pp.Index = "0";
                        pp.integers = "0";
                        pp.prescale = "0";
                        pp.reload = "0";
                        pp.Speed = "0";
                        presc = (sysclk / i) - 1;
                        pp.prescale = presc.ToString();
                        rlod = i * 1000000 / voice_clk;
                        pp.reload = rlod.ToString();
                        dvt =(int) (((rlod*1000)*100/(sysclk / (presc + 1)))/tm0);
                        pp.deviation = dvt.ToString();
                        pp.Index = i.ToString();
                        pp.integers = intg.ToString();
                        pp.decimals = dec.ToString();
                        myList.Add(pp);
                    }
               
            }

        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            myList.Clear();
            showlistView.ItemsSource = null;
            checkvalue();
            showlistView.ItemsSource = myList;
            count++;
           
                //1s ==1000 000 us
               

        }



        private void combox_voice_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            switch (combox_voice.SelectedIndex)
            {
                case 0:
                    voice_clk = 44100;
                    break;
                case 1:
                    voice_clk = 48000;
                    break;
                case 2:
                    voice_clk = 128000;
                    break;
                case 3:
                    voice_clk = 320000;
                    break;


            }
        }

        private void system_clk_TextChanged(object sender, TextChangedEventArgs e)
        {

            try
            {

                sysclk = Convert.ToInt32(system_clk.Text);

            }
            catch
            {

            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            count=0;
        }

        private void accuracy_TextChanged(object sender, TextChangedEventArgs e)
        {
            accuracy_value = Convert.ToInt32(accuracy.Text);
        }
    }
}

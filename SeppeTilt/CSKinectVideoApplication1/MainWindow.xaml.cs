using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Microsoft.Kinect;


namespace CSKinectVideoApplication1
{


    public partial class MainWindow : Window
    {
        //declareren van de sensor
        KinectSensor sensor = KinectSensor.KinectSensors[0];
        byte[] pixelData;


        public MainWindow()
        {
            {
                InitializeComponent();
            }
          
            this.Loaded += new RoutedEventHandler(MainWindow_Loaded);
            this.Unloaded += new RoutedEventHandler(MainWindow_Unloaded);

            sensor.AccelerometerGetCurrentReading();


           
            sensor.ColorStream.Enable();
            // initialiseren van de camera
            

            


        }



        void MainWindow_Unloaded(object sender, RoutedEventArgs e)
        {
            sensor.Stop();
            
        }

        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            sensor.Start();
            sliderLabel.Content = (int)sensor.ElevationAngle; //Label instellen van scroller, pas hier nadat de sensor gestart is.
            sensor.ColorFrameReady += runtime_VideoFrameReady;
            
       

        }

        void runtime_VideoFrameReady(object sender, ColorImageFrameReadyEventArgs e)
        {
            bool receivedData = false;

            using (ColorImageFrame CFrame = e.OpenColorImageFrame())
            {
                if (CFrame == null)
                {
                    // process duurt te lang
                }
                else
                {
                    pixelData = new byte[CFrame.PixelDataLength];
                    CFrame.CopyPixelDataTo(pixelData);
                    receivedData = true;
                    
                }
            }
            

            if (receivedData)
            {
                BitmapSource source = BitmapSource.Create(640, 480, 96, 96,
                        PixelFormats.Bgr32, null, pixelData, 640 * 4);
                
                /*BitmapSource source = BitmapSource.Create(640, 480, 96, 96,
                        PixelFormats.Bgr32, null, pixelData, 640 * 4);
                 */

                video.Source = source; //Nu speel ik mijn bitmap door.
                video2.Source = source; //
            }
        }

        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            int i = new int();
            i = (int)slider.Value;
            sliderLabel.Content = i;

        }

        private void buttonRichten_Click(object sender, RoutedEventArgs e)
        {
            sensor.ElevationAngle = (int)slider.Value;
        }


        
        

        
    }
}

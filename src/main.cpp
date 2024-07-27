#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <qhyccd.h>

class QhyCamera
{
  public:
    QhyCamera()
    {
      char id[32];
      auto ret = InitQHYCCDResource();
      if (ret == QHYCCD_SUCCESS)
      {
        m_ncameras = ScanQHYCCD();
        if (m_ncameras > 0)
        {
          for (int i=0; i<m_ncameras; i++)
          {
            auto status = GetQHYCCDId(i, id);
            std::string s = id;
            m_cameras.push_back(s);
          }
        }
        else {
          std::cout << "Init QHYCCD unsuccessful";
        };
      };
    };

    auto numcameras()
    {
      return m_ncameras;
    };

    auto getCamID(int i)
    {
      try 
      {
        auto camid = m_cameras[i];
        return camid;
      }
      catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        std::string camid;
        return camid;
      }
    };

  private:
    int m_ncameras = 0;
    std::vector<std::string> m_cameras;
};

int main()
{
  QhyCamera camera;
  for (int i=0; i<camera.numcameras(); i++)
  {
    try
    {
      auto camid = camera.getCamID(i);
      std::cout << "Camera " << i << "has camid=" << camid << std::endl;
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  }
}

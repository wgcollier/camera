#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <qhyccd.h>

class QhyCameraException : public std::exception
{
  public:
    QhyCameraException(std::string msg) : m_message(msg) {}
    const char* what() {return m_message.c_str();}

  private:
    std::string m_message;
};

class QhyResource
{
  public:
    QhyResource()
    {
      char id[32];
      auto ret = InitQHYCCDResource();
      if (ret == QHYCCD_SUCCESS)
      {
        auto ncam = ScanQHYCCD();
        if (ncam > 0)
        {
          m_ncameras = ncam;
          for (int i=0; i<m_ncameras; i++)
          {
            auto status = GetQHYCCDId(i, id);
            std::string s = id;
            m_cameras.push_back(s);
          }
        }
        else {
          std::cout << "Init QHYCCD Scan unsuccessful;  ncam=" << ncam << std::endl;
        };
      }
      else {
        std::cout << "Init QHYCCD unsuccessful;  ret=" << ret << std::endl;
      };
    };

    ~QhyResource()
    {
      auto ret = QHYCCD_ERROR;
      ret = ReleaseQHYCCDResource();
      if (ret == QHYCCD_SUCCESS)
      {
        std::cout << "QhyResource Released" << std::endl;
      }
      else
      {
        std::cout << "QhyResource release was unsuccessful." << std::endl;
      }
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

class QhyCamera
{
  public:
    QhyCamera(std::string camid)
    {
      std::cout << "Constructing QhyCamera class for " << camid << std::endl;
      m_cameraid = new char [camid.length()+1];
      std::strcpy(m_cameraid, camid.c_str());
      m_camhandle = OpenQHYCCD(m_cameraid);
      if (m_camhandle == NULL)
      {
        std::stringstream ss;
        ss << "Unable to open camera: " << camid;
        std::string str(ss.str());
        throw QhyCameraException(str);
      }
      std::cout << "QhyCamera " << m_cameraid << " complete." << std::endl;
    }

    ~QhyCamera()
    {
      if (m_camhandle != NULL)
      {
        auto ret = QHYCCD_ERROR;
        ret = CloseQHYCCD(m_camhandle);
        if (ret != QHYCCD_SUCCESS)
        {
          std::cout << "Unable to close camera " << m_cameraid << ":" << m_camhandle << std::endl;
        }
      }
      std::cout << "Closed QhyCamera " << m_cameraid << ":" << m_camhandle << std::endl;
    }

    std::string info()
    {
      std::stringstream ss;
      ss << "Camera: " << "id=" << m_cameraid << " " << "handle=" << m_camhandle;
      std::string str(ss.str());
      return str;
    }

  private:
    char* m_cameraid;
    qhyccd_handle* m_camhandle;
};

int main()
{
  QhyResource qhyresources;
  for (int i=0; i<qhyresources.numcameras(); i++)
  {
    try
    {
      auto camid = qhyresources.getCamID(i);
      std::cout << "Camera " << i << "has camid=" << camid << std::endl;
      QhyCamera cam(camid);
      std::cout << "Constructed " << cam.info() << std::endl;
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  }
}

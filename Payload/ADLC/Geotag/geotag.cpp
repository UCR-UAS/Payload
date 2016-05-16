#include <exiv2/exiv2.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/metadatum.hpp>
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;


//coordinates are to be in this format "5/7 6/5 5/8"
void addGeoTag(string file,string longi, string lati)
{
  Exiv2::ExifData exifData;

      Exiv2::URationalValue::AutoPtr rv(new Exiv2::URationalValue);
      rv->read(longi);
      Exiv2::ExifKey key = Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude");
      exifData.add(key, rv.get());
      Exiv2::ExifKey key1 = Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude");
      rv->read(lati);
      exifData.add(key, rv.get());
      Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
      assert(image.get() != 0);
      image->setExifData(exifData);
      image->writeMetadata();

}


int main()
{
  string file;
  string longi;
  string lati;
  cin >> file;
  getline(cin,longi);
  getline(cin,lati);
  addGeoTag(file,longi,lati);
  return 0;
}

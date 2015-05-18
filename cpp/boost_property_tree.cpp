#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
namespace pt = boost::property_tree;

/*
 <converters>
  <camera>
    <name>depth</name>
    <resolution>VGA</resolution>
    <fps>15</fps>
  </camera>
  <camera>
    <name>ir</name>
    <resolution>QQGVA</resolution>
    <fps>5</fps>
  </camera>
</converters>
*/

int main()
{
  pt::ptree tree;
  pt::read_xml( "boost_property_tree.xml", tree );

  std::string depth_camera_res = tree.get( "converters.depth_camera.resolution", "VGA" );
  std::cout << "[xml] found depth camera resolution: " << depth_camera_res << std::endl;

  //pt::ptree tree;
  pt::read_json( "boost_property_tree.json", tree );

  depth_camera_res = tree.get( "converters.depth_camera.resolution", "VGA" );
  std::cout << "[json] found depth camera resolution: " << depth_camera_res << std::endl;

  if ( depth_camera_res == "QVGA" )
  {
    tree.put( "converters.depth_camera.resolution", 3 );
  }
  depth_camera_res = tree.get( "converters.depth_camera.resolution", "VGA" );
  std::cout << "[json] found depth camera resolution: " << depth_camera_res << std::endl;
}

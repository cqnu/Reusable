#ifndef basic_types_hpp
#define basic_types_hpp


// I think this has to come before STL?
#include <boost/config.hpp>


// ===========================================
// All the STL support we need
// ===========================================
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_map>		// for C++11 unordered_map and unordered_multimap
#include <unordered_set>
// ===========================================


// My STL container extensions (ie sorted_vector)
#include "STLContainers.h"


// ===========================================
// Basic boost support
// ===========================================
// for boost::split(), replace_all()
#include <boost/algorithm/string.hpp>

// boost assign
// used for:
//      std::vector<int> v = boost::assign::list_of(1)(2)(3);
// REPLACE once c++11 is available:
//      std::vector<int> v = {1,2,3};
#include <boost/assign.hpp>

// for checksum functions
#include <boost/crc.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

// ranged for loops with an index:
//      for (const auto& element : boost::adaptors::index(my_container))
//          cout << element.value() << element.index();
#include <boost/range/adaptor/indexed.hpp>
// ===========================================


// ===========================================
// 32 vs 64 bit ENVIRONMENT CHECK
// ===========================================
// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif
// ===========================================


// ===========================================
// cross-platform threading and i/o
// ===========================================
#ifdef WIN32

	// we need to define the target system
	#define _WIN32_WINNT 0x0501

	// we also need a compiled lib:
	//	libboost_system-vc100-mt-1_53.lib
	//
	// to get it, first build boost:
	//
	//		cd boost
	//		bootstrap.bat
	//		.\b2
	//
	// then add the lib path to the project:
	//	C:\Software Development\boost_1_53_0\stage\lib

#endif
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time.hpp>
// ===========================================


// ===========================================
// https (taken from boost docs)
// ===========================================
#include <boost/asio/ssl.hpp>
using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
// NOTE that we use the form that requires an existing socket.
// See: http://www.boost.org/doc/libs/1_57_0/doc/html/boost_asio/overview/ssl.html
typedef ssl::stream<tcp::socket&> ssl_socket;
typedef ssl::stream<tcp::socket> ssl_embedded_socket;
// ===========================================


// ===========================================
// UUIDs
// ===========================================
// When using this in windows...
// You need to define following macro under Project Properties--> yourapp Properties--> ALL CONFIGS -> C/C++-->Command Connector-->Additional Options
//
//		-D_SCL_SECURE_NO_WARNINGS 
//
// so VS doesn't spew "checked iterators" warnings.
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
// ===========================================


// ===========================================
// graph library (BGL) support
// ===========================================
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/undirected_dfs.hpp>
#include <boost/graph/graphviz.hpp>
// ===========================================


// ===========================================
// writing to and reading from files
// ===========================================
#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
// ===========================================


using namespace std;
using namespace boost;


// ===========================================
// JSON encoding/decoding
// ===========================================
// rapidjson JSON parser, v2.0 from svn
// it's FAST: https://github.com/mloskot/json_benchmark

// We override the default behavior of asserting on parse errors
// with throwing of this exception.  Then we can gracefully handle errors.
class rapidjson_exception : public std::runtime_error
{ 
public:
    rapidjson_exception() : std::runtime_error("json schema invalid") {}
};
#define RAPIDJSON_ASSERT(x)  if(x); else throw rapidjson_exception();

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>       // These two includes allow you to get an object as a string
#include <rapidjson/writer.h>             // That allows an array of objects to use an object parser function

static string json_get_string(rapidjson::Document& d)
{
    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
    d.Accept( writer );
    return sb.GetString();
}

// 2016/03/12 Sure rapidjson is fast but it sucks ass at handling std::string.  No excuse.
static void json_add_string(rapidjson::Document& d, rapidjson::Value& parent, const string& name, const string& value)
{
    rapidjson::Value n;
    n.SetString(name.c_str(),name.size(),d.GetAllocator());
    rapidjson::Value v;
    v.SetString(value.c_str(),value.size(),d.GetAllocator());
    parent.AddMember(n,v,d.GetAllocator());
}


// ===========================================
//   boost XML parsing via property_tree
// ===========================================
// - Does not do SAX-style parsing
// - Messy
// - Uses RapidXML underneath (good i think)
// 
// I'll keep the headers here since we only plan 
// to use it here to extract customer xml.
// 
// NOTE that ptree JSON handling does not preserve 
// int/bool/etc type - rendering it totally useless.
// ===========================================
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
using boost::property_tree::ptree;
// ===========================================


// ===========================================
// COMMON CUSTOM TYPES
// ===========================================

typedef vector<string> Strings;
typedef Strings::iterator StringsIt;
typedef vector<int> Ints;
typedef vector<int>::iterator IntsIt;
typedef vector<int>::const_iterator IntsConstIt;

// our hashmaps
typedef std::unordered_map<std::string, int> hashmap;
typedef std::unordered_multimap<std::string, int> hashmmap;

// RESTful http action verbs
// Used by http_client and http_server
// Search for this on changes:
//	assert(http_action_count == 5);
typedef enum
{
	ha_get,				// for RETRIEVE
	ha_post,			// for CREATE (when using server-generated ID)
	ha_put,				// for UPDATE (also for create when client provides ID)
	ha_patch,			// for UPDATE of a subset of fields (PUT technically requires all)
	ha_delete,			// for DELETE

	http_action_count
} http_action;


// NOTE that for many of our JSON objects, we don't need to permanently store all the data that is extracted.
// Strategy:
//      use a memory object inside a JSON object
//      extract the JSON
//      use the JSON data as needed
//      discard the JSON object and just keep the in-memory object
class JSONableObject
{
public:
    virtual ~JSONableObject() {}

    virtual bool from_JSON(const string& in) = 0;
    virtual string to_JSON() const = 0;
    virtual void log() const {}
};


#endif

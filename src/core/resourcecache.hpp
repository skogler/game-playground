#ifndef RESOURCECACHE_HPP_
#define RESOURCECACHE_HPP_

#include <string>
#include <list>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

template<class T>
class ResourceCache
{
public:
	ResourceCache(const boost::filesystem::path & baseDirectory);
	virtual ~ResourceCache();
	void setBaseDirectory(const std::string & baseDirectory);

	boost::shared_ptr<T> get(const std::string & name);
	bool load(const std::string & name);

protected:
	fs::path baseDirectory;
//	std::vector<fs::path> resourceList;
	std::map<std::string, boost::shared_ptr<T> > loadedResources;

	//void createResourceList();
};

template<class T>
ResourceCache<T>::ResourceCache(const fs::path & baseDirectory) :
		baseDirectory(baseDirectory)
{
	if (!(fs::exists(this->baseDirectory) && fs::is_directory(this->baseDirectory)))
	{
		throw std::runtime_error("Invalid resource directory: " + baseDirectory.string());
	}
	//createResourceList();
}
template<class T>
ResourceCache<T>::~ResourceCache()
{
}

template<class T>
boost::shared_ptr<T> ResourceCache<T>::get(const std::string& name)
{
	typedef typename std::map<std::string, boost::shared_ptr<T> >::iterator It;
	It iter = loadedResources.find(name);

	if (iter == loadedResources.end())
	{
		fs::path filename = baseDirectory / name;
		boost::shared_ptr<T> resource = (new T(filename));
		loadedResources[name] = resource;
		return resource;
	}
	else
	{
		return iter->second();
	}
}

/**
 * Create the list of resources by adding all files in
 * the resource directory. This should save some time
 * when loading resources since there is no disk access
 * needed to search for a file.
 */
//template<class T>
//void ResourceManager<T>::createResourceList()
//{
//	resourceList.clear();
//	for (fs::recursive_directory_iterator end, it(resourceDirectory); it != end; ++it)
//	{
//		fs::path item = *it;
//		if (fs::is_regular_file(item))
//		{
//			resourceList.push_back(item);
//		}
//	}
//}
#endif /* RESOURCECACHE_HPP_ */

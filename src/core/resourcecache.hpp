#ifndef RESOURCECACHE_HPP_
#define RESOURCECACHE_HPP_

#include <string>
#include <list>
#include <map>
#include <boost/filesystem.hpp>

#include "definitions.hpp"
namespace fs = boost::filesystem;

template<class T>
class ResourceCache
{
public:
	ResourceCache(const boost::filesystem::path & baseDirectory, const std::string & fileEnding);
	virtual ~ResourceCache();
	void setBaseDirectory(const std::string & baseDirectory);

	/**
	 * Gets the resource with the specified name.
	 * Name is relative to baseDirectory, the file ending is added automatically.
	 * If not found, throws a runtime error.
	 */
	shared_ptr<T> get(const std::string & name);
	bool load(const std::string & name);

protected:
	fs::path baseDirectory;
	std::string fileEnding;
	std::map<std::string, shared_ptr<T> > loadedResources;

//	std::vector<fs::path> resourceList;
//	void createResourceList();
};

template<class T>
ResourceCache<T>::ResourceCache(const fs::path & baseDirectory, const std::string & fileEnding) :
				baseDirectory(baseDirectory),
				fileEnding(fileEnding)
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
shared_ptr<T> ResourceCache<T>::get(const std::string& name)
{
	typedef typename std::map<std::string, shared_ptr<T> >::iterator It;
	It iter = loadedResources.find(name);

	if (iter == loadedResources.end())
	{
		fs::path path = baseDirectory;
		std::string filename(name); // copy filename
		if(fileEnding != "") // Do not add extension if file ending is empty
		{
			filename += ("." + fileEnding);
		}
		path /= filename;
		if (!(fs::exists(path) && fs::is_regular_file(path)))
		{
			throw std::runtime_error("Resource file not found: " + path.string());
		}
		shared_ptr<T> resource(new T(path));
		loadedResources[name] = resource;
		return resource;
	}
	else
	{
		return iter->second;
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

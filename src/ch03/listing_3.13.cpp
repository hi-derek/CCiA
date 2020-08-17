#include <map>
#include <string>
#include <mutex>

#if __cplusplus >= 201703L
    #include <shared_mutex>
    using namespace std;
#else
    #include <boost/thread/shared_mutex.hpp>
    using namespace boost;
#endif

class dns_entry
{};

class dns_cache
{
    std::map<std::string,dns_entry> entries;
    shared_mutex entry_mutex;
public:
    dns_entry find_entry(std::string const& domain)
    {
        shared_lock<shared_mutex> lk(entry_mutex);
        std::map<std::string,dns_entry>::const_iterator const it=
            entries.find(domain);
        return (it==entries.end())?dns_entry():it->second;
    }
    void update_or_add_entry(std::string const& domain,
                             dns_entry const& dns_details)
    {
        std::lock_guard<shared_mutex> lk(entry_mutex);
        entries[domain]=dns_details;
    }
};

int main()
{}

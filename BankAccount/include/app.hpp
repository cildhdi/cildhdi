#include <vector>
#include <json/json.hpp>
#include <fstream>

#include <account.hpp>
#include <result.hpp>
#include <storage_object.hpp>
#include <options.hpp>
#include <tools.hpp>

namespace ba
{
class App
{
private:
    KEY_WD(std::vector<Account>, _accounts);

    std::string _file;
    Options _options;

private:
    void UpdateOptions();

public:
    nlohmann::json ToJson() const;
    void FromJson(nlohmann::json json);

public:
    App(const std::string &file);
    std::string GetFileName() const;
    void AddAccount(const Account &account);
    Options AccountOptions(Account &account, bool &run);
    int Run();
    void Save() const;
};
} // namespace ba
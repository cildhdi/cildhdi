#include <vector>
#include <json/json.hpp>

#include <account.hpp>
#include <result.hpp>
#include <storage_object.hpp>

namespace ba
{
class App
{
private:
    KEY_WD(std::vector<Account>, _accounts);

private:
    nlohmann::json ToJson() const;
    void FromJson(nlohmann::json json);

public:
    App();
    void AddAccount(const Account &account);
};
} // namespace ba
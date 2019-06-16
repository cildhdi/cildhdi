# 个人银行账户管理程序（起评：中）
某人的活期储蓄账户包括账号，余额，年利率等基本信息，并需要显示账户信息，存款，取款，结算利息等基本操作。
基本功能要求：
设计完成以上基本功能的类，并给出相应的测试程序。
进一步：
- 该用户有多个储蓄账户，增加功能能够记录各个账户的总金额，并增加相应的访问函数。
- 为该用户增加信用账户，注意信用账户与储蓄账户的需求有不同。信用账户的特点是允许透支，每个信用账户也有信用额度，总得透支金额要在这个额度以内。如果向信用账户存钱，不会有利息，但使用信用账户透支则需要支付利息。请重新考虑该程序类的设计与实现。
- 将用户的账户信息保存至文件中。

## 要求
- c++ 14 及以上

## 项目目录
- ```include/``` 项目头文件
- ```src/``` 源文件
- ```lib/``` 第三方库
- ```tests/``` 核心功能单元测试文件


## 第三方库
- [doctest](https://github.com/onqtam/doctest) 用于单元测试
- [json](https://github.com/nlohmann/json) 使用 json 格式保存账号信息

## 测试结果
4 个测试案例总计 104 个测试全部通过。
### BankAccountTest.exe --s 输出
```
[doctest] doctest version is "2.3.3"
[doctest] run with "--help" for options
===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  Constructor

../tests/account_test.cpp:13: SUCCESS: CHECK_EQ( account.GetUserName(), "" ) is correct!
  values: CHECK_EQ( ,  )

../tests/account_test.cpp:14: SUCCESS: CHECK_EQ( account.GetAccountType(), ba::AccountType::kDebit ) is correct!
  values: CHECK_EQ( 0, 0 )

../tests/account_test.cpp:15: SUCCESS: CHECK_EQ( account.GetRate(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

../tests/account_test.cpp:16: SUCCESS: CHECK_EQ( account.GetLimit(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

../tests/account_test.cpp:17: SUCCESS: CHECK_EQ( account.GetBalance(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

../tests/account_test.cpp:23: SUCCESS: CHECK_EQ( account.GetUserName(), "User" ) is correct!
  values: CHECK_EQ( User, User )

../tests/account_test.cpp:24: SUCCESS: CHECK_EQ( account.GetAccountType(), ba::AccountType::kCredit ) is correct!
  values: CHECK_EQ( 1, 1 )

../tests/account_test.cpp:25: SUCCESS: CHECK_EQ( account.GetRate(), 0.05 ) is correct!
  values: CHECK_EQ( 0.05, 0.05 )

../tests/account_test.cpp:26: SUCCESS: CHECK_EQ( account.GetLimit(), 0.06 ) is correct!
  values: CHECK_EQ( 0.06, 0.06 )

../tests/account_test.cpp:27: SUCCESS: CHECK_EQ( account.GetBalance(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  DebitAccount

../tests/account_test.cpp:35: SUCCESS: CHECK_EQ( account.GetUserName(), "User" ) is correct!
  values: CHECK_EQ( User, User )

../tests/account_test.cpp:36: SUCCESS: CHECK_EQ( account.GetAccountType(), ba::AccountType::kDebit ) is correct!
  values: CHECK_EQ( 0, 0 )

../tests/account_test.cpp:37: SUCCESS: CHECK_EQ( account.GetRate(), 0.1 ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:38: SUCCESS: CHECK_EQ( account.GetLimit(), 0 ) is correct!
  values: CHECK_EQ( 0.0, 0 )

../tests/account_test.cpp:39: SUCCESS: CHECK_EQ( account.GetBalance(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  DebitAccount
  Deposit

../tests/account_test.cpp:47: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:48: SUCCESS: CHECK_EQ( account.GetBalance(), 100.0 ) is correct!
  values: CHECK_EQ( 100.0, 100.0 )

../tests/account_test.cpp:54: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:55: SUCCESS: CHECK_EQ( account.GetBalance(), 100 + 100 * 0.1 + 100 ) is correct!
  values: CHECK_EQ( 210.0, 210.0 )

../tests/account_test.cpp:61: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:62: SUCCESS: CHECK_EQ( account.GetBalance(), 210 + 210.0 * 0.1 * 2 + 100 ) is correct!
  values: CHECK_EQ( 352.0, 352.0 )

../tests/account_test.cpp:65: SUCCESS: CHECK( !r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:66: SUCCESS: CHECK_EQ( account.GetBalance(), 210 + 210.0 * 0.1 * 2 + 100 ) is correct!
  values: CHECK_EQ( 352.0, 352.0 )

{
    "_account_type": 0,
    "_changes": [
        {
            "balance": 100.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 0
        },
        {
            "balance": 110.0,
            "change": 10.0,
            "detail": "interest",
            "time": 86400
        },
        {
            "balance": 210.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 86400
        },
        {
            "balance": 252.0,
            "change": 42.0,
            "detail": "interest",
            "time": 259200
        },
        {
            "balance": 352.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 259200
        }
    ],
    "_limit": 0.0,
    "_rate": 0.1,
    "_user_name": "User"
}
../tests/account_test.cpp:73: SUCCESS: CHECK_EQ( account.GetAccountType(), _account.GetAccountType() ) is correct!
  values: CHECK_EQ( 0, 0 )

../tests/account_test.cpp:74: SUCCESS: CHECK_EQ( account.GetBalance(), _account.GetBalance() ) is correct!
  values: CHECK_EQ( 352.0, 352.0 )

../tests/account_test.cpp:75: SUCCESS: CHECK_EQ( account.GetLimit(), _account.GetLimit() ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

../tests/account_test.cpp:76: SUCCESS: CHECK_EQ( account.GetRate(), _account.GetRate() ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:77: SUCCESS: CHECK_EQ( account.GetUserName(), _account.GetUserName() ) is correct!
  values: CHECK_EQ( User, User )

                          时间            金额变化      余额            详细信息
================================================================================
      Sun Jan 04 08:00:00 1970         +100.000000       352             Deposit
      Sun Jan 04 08:00:00 1970          +42.000000       252            interest
      Fri Jan 02 08:00:00 1970         +100.000000       210             Deposit
      Fri Jan 02 08:00:00 1970          +10.000000       110            interest
      Thu Jan 01 08:00:00 1970         +100.000000       100             Deposit
===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  DebitAccount

../tests/account_test.cpp:35: SUCCESS: CHECK_EQ( account.GetUserName(), "User" ) is correct!
  values: CHECK_EQ( User, User )

../tests/account_test.cpp:36: SUCCESS: CHECK_EQ( account.GetAccountType(), ba::AccountType::kDebit ) is correct!
  values: CHECK_EQ( 0, 0 )

../tests/account_test.cpp:37: SUCCESS: CHECK_EQ( account.GetRate(), 0.1 ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:38: SUCCESS: CHECK_EQ( account.GetLimit(), 0 ) is correct!
  values: CHECK_EQ( 0.0, 0 )

../tests/account_test.cpp:39: SUCCESS: CHECK_EQ( account.GetBalance(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  DebitAccount
  Withdraw

../tests/account_test.cpp:88: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:89: SUCCESS: CHECK_EQ( account.GetBalance(), 100.0 ) is correct!
  values: CHECK_EQ( 100.0, 100.0 )

../tests/account_test.cpp:95: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:96: SUCCESS: CHECK_EQ( account.GetBalance(), 100.0 * 0.1 ) is correct!
  values: CHECK_EQ( 10.0, 10.0 )

../tests/account_test.cpp:99: SUCCESS: CHECK( !r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:100: SUCCESS: CHECK_EQ( account.GetBalance(), 100.0 * 0.1 ) is correct!
  values: CHECK_EQ( 10.0, 10.0 )

../tests/account_test.cpp:103: SUCCESS: CHECK( !r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:104: SUCCESS: CHECK_EQ( account.GetBalance(), 100.0 * 0.1 ) is correct!
  values: CHECK_EQ( 10.0, 10.0 )

{
    "_account_type": 0,
    "_changes": [
        {
            "balance": 100.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 0
        },
        {
            "balance": 110.0,
            "change": 10.0,
            "detail": "interest",
            "time": 86400
        },
        {
            "balance": 10.0,
            "change": -100.0,
            "detail": "Withdraw",
            "time": 86400
        },
        {
            "balance": 10.0,
            "change": 0.0,
            "detail": "interest",
            "time": 86400
        }
    ],
    "_limit": 0.0,
    "_rate": 0.1,
    "_user_name": "User"
}
../tests/account_test.cpp:111: SUCCESS: CHECK_EQ( account.GetAccountType(), _account.GetAccountType() ) is correct!
  values: CHECK_EQ( 0, 0 )

../tests/account_test.cpp:112: SUCCESS: CHECK_EQ( account.GetBalance(), _account.GetBalance() ) is correct!
  values: CHECK_EQ( 10.0, 10.0 )

../tests/account_test.cpp:113: SUCCESS: CHECK_EQ( account.GetLimit(), _account.GetLimit() ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

../tests/account_test.cpp:114: SUCCESS: CHECK_EQ( account.GetRate(), _account.GetRate() ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:115: SUCCESS: CHECK_EQ( account.GetUserName(), _account.GetUserName() ) is correct!
  values: CHECK_EQ( User, User )

                          时间            金额变化      余额            详细信息
================================================================================
      Fri Jan 02 08:00:00 1970            0.000000        10            interest
      Fri Jan 02 08:00:00 1970         -100.000000        10            Withdraw
      Fri Jan 02 08:00:00 1970          +10.000000       110            interest
      Thu Jan 01 08:00:00 1970         +100.000000       100             Deposit
===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  CreditAccount

../tests/account_test.cpp:124: SUCCESS: CHECK_EQ( account.GetUserName(), "User" ) is correct!
  values: CHECK_EQ( User, User )

../tests/account_test.cpp:125: SUCCESS: CHECK_EQ( account.GetAccountType(), ba::AccountType::kCredit ) is correct!
  values: CHECK_EQ( 1, 1 )

../tests/account_test.cpp:126: SUCCESS: CHECK_EQ( account.GetRate(), 0.1 ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:127: SUCCESS: CHECK_EQ( account.GetLimit(), 100 ) is correct!
  values: CHECK_EQ( 100.0, 100 )

../tests/account_test.cpp:128: SUCCESS: CHECK_EQ( account.GetBalance(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  CreditAccount
  Deposit

../tests/account_test.cpp:136: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:137: SUCCESS: CHECK_EQ( account.GetBalance(), 100.0 ) is correct!
  values: CHECK_EQ( 100.0, 100.0 )

../tests/account_test.cpp:143: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:144: SUCCESS: CHECK_EQ( account.GetBalance(), 200.0 ) is correct!
  values: CHECK_EQ( 200.0, 200.0 )

../tests/account_test.cpp:150: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:151: SUCCESS: CHECK_EQ( account.GetBalance(), 300 ) is correct!
  values: CHECK_EQ( 300.0, 300 )

../tests/account_test.cpp:154: SUCCESS: CHECK( !r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:155: SUCCESS: CHECK_EQ( account.GetBalance(), 300 ) is correct!
  values: CHECK_EQ( 300.0, 300 )

{
    "_account_type": 1,
    "_changes": [
        {
            "balance": 100.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 0
        },
        {
            "balance": 100.0,
            "change": 0.0,
            "detail": "interest",
            "time": 86400
        },
        {
            "balance": 200.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 86400
        },
        {
            "balance": 200.0,
            "change": 0.0,
            "detail": "interest",
            "time": 259200
        },
        {
            "balance": 300.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 259200
        }
    ],
    "_limit": 100.0,
    "_rate": 0.1,
    "_user_name": "User"
}
../tests/account_test.cpp:162: SUCCESS: CHECK_EQ( account.GetAccountType(), _account.GetAccountType() ) is correct!
  values: CHECK_EQ( 1, 1 )

../tests/account_test.cpp:163: SUCCESS: CHECK_EQ( account.GetBalance(), _account.GetBalance() ) is correct!
  values: CHECK_EQ( 300.0, 300.0 )

../tests/account_test.cpp:164: SUCCESS: CHECK_EQ( account.GetLimit(), _account.GetLimit() ) is correct!
  values: CHECK_EQ( 100.0, 100.0 )

../tests/account_test.cpp:165: SUCCESS: CHECK_EQ( account.GetRate(), _account.GetRate() ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:166: SUCCESS: CHECK_EQ( account.GetUserName(), _account.GetUserName() ) is correct!
  values: CHECK_EQ( User, User )

                          时间            金额变化      余额            详细信息
================================================================================
      Sun Jan 04 08:00:00 1970         +100.000000       300             Deposit
      Sun Jan 04 08:00:00 1970            0.000000       200            interest
      Fri Jan 02 08:00:00 1970         +100.000000       200             Deposit
      Fri Jan 02 08:00:00 1970            0.000000       100            interest
      Thu Jan 01 08:00:00 1970         +100.000000       100             Deposit
===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  CreditAccount

../tests/account_test.cpp:124: SUCCESS: CHECK_EQ( account.GetUserName(), "User" ) is correct!
  values: CHECK_EQ( User, User )

../tests/account_test.cpp:125: SUCCESS: CHECK_EQ( account.GetAccountType(), ba::AccountType::kCredit ) is correct!
  values: CHECK_EQ( 1, 1 )

../tests/account_test.cpp:126: SUCCESS: CHECK_EQ( account.GetRate(), 0.1 ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:127: SUCCESS: CHECK_EQ( account.GetLimit(), 100 ) is correct!
  values: CHECK_EQ( 100.0, 100 )

../tests/account_test.cpp:128: SUCCESS: CHECK_EQ( account.GetBalance(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

===============================================================================
../tests/account_test.cpp:6:
TEST CASE:  Account
  CreditAccount
  Withdraw

../tests/account_test.cpp:177: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:178: SUCCESS: CHECK_EQ( account.GetBalance(), 100.0 ) is correct!
  values: CHECK_EQ( 100.0, 100.0 )

../tests/account_test.cpp:184: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:185: SUCCESS: CHECK_EQ( account.GetBalance(), 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

../tests/account_test.cpp:188: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:189: SUCCESS: CHECK_EQ( account.GetBalance(), -100.0 ) is correct!
  values: CHECK_EQ( -100.0, -100.0 )

../tests/account_test.cpp:195: SUCCESS: CHECK( !r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:196: SUCCESS: CHECK_EQ( account.GetBalance(), -120.0 ) is correct!
  values: CHECK_EQ( -120.0, -120.0 )

../tests/account_test.cpp:199: SUCCESS: CHECK( !r.success ) is correct!
  values: CHECK( true )

../tests/account_test.cpp:200: SUCCESS: CHECK_EQ( account.GetBalance(), -120.0 ) is correct!
  values: CHECK_EQ( -120.0, -120.0 )

{
    "_account_type": 1,
    "_changes": [
        {
            "balance": 100.0,
            "change": 100.0,
            "detail": "Deposit",
            "time": 0
        },
        {
            "balance": 100.0,
            "change": 0.0,
            "detail": "interest",
            "time": 86400
        },
        {
            "balance": 0.0,
            "change": -100.0,
            "detail": "Withdraw",
            "time": 86400
        },
        {
            "balance": 0.0,
            "change": 0.0,
            "detail": "interest",
            "time": 86400
        },
        {
            "balance": -100.0,
            "change": -100.0,
            "detail": "Withdraw",
            "time": 86400
        },
        {
            "balance": -120.0,
            "change": -20.0,
            "detail": "interest",
            "time": 259200
        }
    ],
    "_limit": 100.0,
    "_rate": 0.1,
    "_user_name": "User"
}
../tests/account_test.cpp:207: SUCCESS: CHECK_EQ( account.GetAccountType(), _account.GetAccountType() ) is correct!
  values: CHECK_EQ( 1, 1 )

../tests/account_test.cpp:208: SUCCESS: CHECK_EQ( account.GetBalance(), _account.GetBalance() ) is correct!
  values: CHECK_EQ( -120.0, -120.0 )

../tests/account_test.cpp:209: SUCCESS: CHECK_EQ( account.GetLimit(), _account.GetLimit() ) is correct!
  values: CHECK_EQ( 100.0, 100.0 )

../tests/account_test.cpp:210: SUCCESS: CHECK_EQ( account.GetRate(), _account.GetRate() ) is correct!
  values: CHECK_EQ( 0.1, 0.1 )

../tests/account_test.cpp:211: SUCCESS: CHECK_EQ( account.GetUserName(), _account.GetUserName() ) is correct!
  values: CHECK_EQ( User, User )

                          时间            金额变化      余额            详细信息
================================================================================
      Sun Jan 04 08:00:00 1970          -20.000000      -120            interest
      Fri Jan 02 08:00:00 1970         -100.000000      -100            Withdraw
      Fri Jan 02 08:00:00 1970            0.000000         0            interest
      Fri Jan 02 08:00:00 1970         -100.000000         0            Withdraw
      Fri Jan 02 08:00:00 1970            0.000000       100            interest
      Thu Jan 01 08:00:00 1970         +100.000000       100             Deposit
===============================================================================
../tests/app_test.cpp:6:
TEST CASE:  App
  Constructor

../tests/app_test.cpp:13: SUCCESS: CHECK_EQ( app.GetFileName(), filename ) is correct!
  values: CHECK_EQ( ,  )

{
    "_accounts": [
        {
            "_account_type": 0,
            "_changes": [],
            "_limit": 0.0,
            "_rate": 0.1,
            "_user_name": "User"
        },
        {
            "_account_type": 1,
            "_changes": [],
            "_limit": 100.0,
            "_rate": 0.1,
            "_user_name": "User"
        }
    ]
}
===============================================================================
../tests/change_test.cpp:7:
TEST CASE:  Change
  ConstructorTest

../tests/change_test.cpp:12: SUCCESS: CHECK_EQ( change.time, 0 ) is correct!
  values: CHECK_EQ( 0, 0 )

../tests/change_test.cpp:13: SUCCESS: CHECK_EQ( change.change, 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

../tests/change_test.cpp:14: SUCCESS: CHECK_EQ( change.detail, "" ) is correct!
  values: CHECK_EQ( ,  )

../tests/change_test.cpp:15: SUCCESS: CHECK_EQ( change.balance, 0.0 ) is correct!
  values: CHECK_EQ( 0.0, 0.0 )

===============================================================================
../tests/change_test.cpp:7:
TEST CASE:  Change
  FromJsonTest

../tests/change_test.cpp:31: SUCCESS: CHECK_EQ( change.time, 123 ) is correct!
  values: CHECK_EQ( 123, 123 )

../tests/change_test.cpp:32: SUCCESS: CHECK_EQ( change.change, 10.0 ) is correct!
  values: CHECK_EQ( 10.0, 10.0 )

../tests/change_test.cpp:33: SUCCESS: CHECK_EQ( change.detail, "interest" ) is correct!
  values: CHECK_EQ( interest, interest )

../tests/change_test.cpp:34: SUCCESS: CHECK_EQ( change.balance, 56.8 ) is correct!
  values: CHECK_EQ( 56.8, 56.8 )

{
    "balance": 56.8,
    "change": 10.0,
    "detail": "interest",
    "time": 123
}
===============================================================================
../tests/change_test.cpp:7:
TEST CASE:  Change
  ToJsonTest

../tests/change_test.cpp:47: SUCCESS: REQUIRE( json.contains(change.time_key) ) is correct!
  values: REQUIRE( true )

../tests/change_test.cpp:48: SUCCESS: CHECK_EQ( json[change.time_key], 123 ) is correct!
  values: CHECK_EQ( 123, 123 )

../tests/change_test.cpp:50: SUCCESS: REQUIRE( json.contains(change.change_key) ) is correct!
  values: REQUIRE( true )

../tests/change_test.cpp:51: SUCCESS: CHECK_EQ( json[change.change_key], 10.0 ) is correct!
  values: CHECK_EQ( 10.0, 10.0 )

../tests/change_test.cpp:53: SUCCESS: REQUIRE( json.contains(change.detail_key) ) is correct!
  values: REQUIRE( true )

../tests/change_test.cpp:54: SUCCESS: CHECK_EQ( json[change.detail_key], "interest" ) is correct!
  values: CHECK_EQ( "interest", interest )

../tests/change_test.cpp:56: SUCCESS: REQUIRE( json.contains(change.balance_key) ) is correct!
  values: REQUIRE( true )

../tests/change_test.cpp:57: SUCCESS: CHECK_EQ( json[change.balance_key], 56.8 ) is correct!
  values: CHECK_EQ( 56.8, 56.8 )

===============================================================================
../tests/result_test.cpp:5:
TEST CASE:  Result

../tests/result_test.cpp:9: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/result_test.cpp:14: SUCCESS: CHECK( r.success ) is correct!
  values: CHECK( true )

../tests/result_test.cpp:19: SUCCESS: CHECK( !r.success ) is correct!
  values: CHECK( true )

===============================================================================
[doctest] test cases:      4 |      4 passed |      0 failed |      0 skipped
[doctest] assertions:    104 |    104 passed |      0 failed |
[doctest] Status: SUCCESS!
```
#include <iostream>
#include <stdexcept> 
#include <iomanip>  

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNum, double initialBalance, double interest) {
        if (initialBalance < 0) {
            throw invalid_argument("Начальный баланс не может быть отрицательным");
        }
        this->accountNumber = accNum;
        this->balance = initialBalance;
        this->interestRate = interest;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма перевода");
        }
        balance += amount;
        cout << "Средства успешно внесены. Остаток на счёте: " << fixed << setprecision(2) << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма снятия.");
        }
        if (amount > balance) {
            throw invalid_argument("Недостаточно средств для снятия.");
        }
        balance -= amount;
        cout << "Средства успешно сняты. Остаток на счёте: " << fixed << setprecision(2) << balance << endl;
    }

    double getBalance() {
        return balance;
    }

    double getInterest() {
        return balance * interestRate * (1.0 / 12.0);
    }

    void setInterestRate(double newRate) {
        interestRate = newRate;
        cout << "Процентная ставка успешно обновлена." << endl;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    static bool transfer(BankAccount& from, BankAccount& to, double amount) {
        if (amount <= 0) {
            cout << "Некорректная сумма перевода." << endl;
            return false;
        }
        if (amount > from.balance) {
            cout << "Недостаточно средств на счёте для перевода." << endl;
            return false;
        }
        from.balance -= amount;
        to.balance += amount;
        cout << "Перевод успешно выполнен. Остаток на счёте отправителя: " << fixed << setprecision(2) << from.balance << ". Остаток на счёте получателя: " << fixed << setprecision(2) << to.balance << endl;
        return true;
    }
};

int main() {
    try {
        BankAccount acc1(1001, 5000.0, 0.03);
        BankAccount acc2(1002, 3000.0, 0.02);

        acc1.deposit(1000.0);
        acc2.withdraw(500.0);
        cout << "Баланс на счёте acc1: " << fixed << setprecision(2) << acc1.getBalance() << endl;
        cout << "Баланс на счёте acc2: " << fixed << setprecision(2) << acc2.getBalance() << endl;
        acc1.setInterestRate(0.035);
        cout << "Проценты, заработанные на счёте acc1: " << fixed << setprecision(2) << acc1.getInterest() << endl;

        cout << "Попытка перевода 2000 со счёта acc1 на счёт acc2:" << endl;
        BankAccount::transfer(acc1, acc2, 2000.0);
        cout << "Баланс на счёте acc1: " << fixed << setprecision(2) << acc1.getBalance() << endl;
        cout << "Баланс на счёте acc2: " << fixed << setprecision(2) << acc2.getBalance() << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}

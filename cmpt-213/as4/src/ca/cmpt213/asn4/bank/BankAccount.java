package ca.cmpt213.asn4.bank;

/**
 * BankAccount class is responsible for maintaining bank account state.
 */

public class BankAccount {
    private double balance;
    private int numDeposits;
    private int numWithdrawals;
    private final double annualInterestRate;
    private double monthlyCharges;

    public BankAccount(double bal, double interestRate) throws IllegalArgumentException {
        if (bal < 0) {
            throw new IllegalArgumentException("Balance is negative (" + bal + ")");
        }
        if (interestRate < 0) {
            throw new IllegalArgumentException("Interest rate is negative (" + interestRate + ")");
        }
        balance = bal;
        annualInterestRate = interestRate;
        numDeposits = 0;
        numWithdrawals = 0;
        monthlyCharges = 0;
    }

    public double deposit(double amount) throws IllegalArgumentException {
        if (amount < 0) {
            throw new IllegalArgumentException("Amount is negative (" + amount + ")");
        }
        this.balance += amount;
        this.numDeposits++;
        return amount;
    }

    public double withdraw(double amount) throws IllegalArgumentException {
        if (amount < 0) {
            throw new IllegalArgumentException("Amount is negative (" + amount + ")");
        }
        this.balance -= amount;
        this.numWithdrawals++;
        return amount;
    }

    public void calcInterest() {
        double monthlyInterest = balance * (annualInterestRate/12d);
        this.balance += monthlyInterest;
    }

    public void monthlyProcess() {
        this.balance -= monthlyCharges;
        calcInterest();
        this.numDeposits = 0;
        this.numWithdrawals = 0;
        this.monthlyCharges = 0;
    }

    public double getBalance() {
        return balance;
    }

    public double getAnnualInterestRate() {
        return annualInterestRate;
    }

    public int getNumDeposits() {
        return numDeposits;
    }

    public int getNumWithdrawals() {
        return numWithdrawals;
    }

    public void setMonthlyCharges(int charges) {
        this.monthlyCharges = charges;
    }
}

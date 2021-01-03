package ca.cmpt213.asn4.bank;

/**
 * SavingsAccount class extends BankAccount to calculate monthly interest based on number
 * of withdrawals from the account, and maintains whether or not the BankAccount is active.
 */

public class SavingsAccount extends BankAccount {
    private boolean isActive;

    public SavingsAccount(double bal, double intRate) throws IllegalArgumentException {
        super(bal, intRate);
        isActive = bal >= 25d;
    }

    @Override
    public double withdraw(double amount) throws IllegalArgumentException {
        double withdrew = 0;
        if (isActive) {
            withdrew = super.withdraw(amount);
        } else {
            System.out.println("Account is not currently active (balance is less than $25).");
        }
        if (super.getBalance() < 25d) {
            isActive = false;
        }
        return withdrew;
    }

    @Override
    public double deposit(double amount) throws IllegalArgumentException {
        super.deposit(amount);
        if (super.getBalance() >= 25d) {
            isActive = true;
        }
        return amount;
    }

    @Override
    public void monthlyProcess() {
        int numWithdrawals = super.getNumWithdrawals();
        if (numWithdrawals > 4) {
            super.setMonthlyCharges(numWithdrawals - 4);
        }
        super.monthlyProcess();
        if (super.getBalance() < 25d) {
            this.isActive = false;
        }
    }
}

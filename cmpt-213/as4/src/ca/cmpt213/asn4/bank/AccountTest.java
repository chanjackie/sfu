package ca.cmpt213.asn4.bank;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AccountTest {

    @Test
    void withdraw() {
        SavingsAccount acc = new SavingsAccount(100, 0.03);
        double amount = 25;
        acc.withdraw(amount);
        assertEquals(75, acc.getBalance());
        assertThrows(IllegalArgumentException.class, () -> acc.withdraw(-25));
        acc.withdraw(60);
        assertEquals(15, acc.getBalance());
        acc.withdraw(5);
        assertEquals(15, acc.getBalance());
    }

    @Test
    void deposit() {
        SavingsAccount acc = new SavingsAccount(0, 0.03);
        double amount = 16.72;
        acc.deposit(amount);
        assertEquals(16.72, acc.getBalance());
        assertThrows(IllegalArgumentException.class, () -> acc.deposit(-25));
        acc.withdraw(10);
        assertEquals(16.72, acc.getBalance());
        acc.deposit(10);
        assertEquals(26.72, acc.getBalance());
        acc.withdraw(5);
        assertEquals(21.72, acc.getBalance());
    }

    @Test
    void monthlyProcess() {
        SavingsAccount acc = new SavingsAccount(100, 0.03);
        acc.monthlyProcess();
        assertEquals(100.25, acc.getBalance());
        for (int i = 0; i < 5; i++) {
            acc.withdraw(0.05);
        }
        assertEquals(100, Math.round(acc.getBalance()));
        acc.monthlyProcess();
        assertEquals(99.2475, Math.round(acc.getBalance()*10000)/10000d);

    }

}
package sfu.cmpt213.as1;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Tokidex tokidex = new Tokidex();
        Scanner sc = new Scanner(System.in);
        int input = 0;
        MenuUtils.printHeader("Tokidex by Jackie Chan sn 301310345");
        while (input != 6) {
            MenuUtils.displayMainMenu();
            System.out.print("> ");
            input = sc.nextInt();
            switch(input) {
                case 1:
                    MenuUtils.displayAllTokis(tokidex);
                    break;
                case 2:
                    MenuUtils.addNewToki(tokidex);
                    break;
                case 3:
                    MenuUtils.deleteToki(tokidex);
                    break;
                case 4:
                    MenuUtils.alterToki(tokidex);
                    break;
                case 5:
                    MenuUtils.dumpTokis(tokidex);
                    break;
                case 6:
                    break;
                default:
                    System.out.println("Please select a valid option from the menu.");
            }
        }
        MenuUtils.printHeader("Goodbye!");

    }
}

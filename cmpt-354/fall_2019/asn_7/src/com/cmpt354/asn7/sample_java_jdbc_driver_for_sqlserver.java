package com.cmpt354.asn7;
/*

For testing SQL Server connection in CSIL through JDBC connection.

Author: Johnny Zhang

You should run this program on a CSIL system.

Last modified @ 2018.03.29, 2008.12.20

*/

/*
Please modify this program before using.

alternation includes: username and password for CSIL SQL Server standard login

note: the JDBC jar file must be on the variable CLASSPATH

*/
import java.sql.*;

class sample_java_jdbc_driver_for_sqlserver {
    private static Connection con;
    private static String space = "                                           ";

    public static void main(String[] args)
    {
        PreparedStatement pstmt = null;
        ResultSet rs;
        String sSQL= "select * from helpdesk";	//the table was created by helpdesk
        String temp="";

        String sUsername = "jgc11";
        String sPassword= "367E22e64N6Hg2Nb";
        // ^^^ modify these 2 lines before compiling this program
        // please replace the username with your CCN id
        // please get the password from table 'helpdesk' of your course database

        String connectionUrl = "jdbc:sqlserver://cypress;" +
                "user = " + sUsername + ";" +
                "password = " + sPassword;

        //System.out.println("\n connectionUrl = " + connectionUrl + "\n\n");

        try
        {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
        }catch(ClassNotFoundException ce)
        {
            System.out.println("\n\nNo JDBC Driver for SQL Server; exit now.\n\n");
            return;
        }

        try
        {
            con = DriverManager.getConnection(connectionUrl);
        }catch (SQLException se)
        {
            System.out.println("\n\nFail to connect to CSIL SQL Server; exit now.\n\n");
            return;
        }

        try
        {
            pstmt = con.prepareStatement(sSQL);
            rs = pstmt.executeQuery();

            System.out.println("\nThe table 'helpdesk' contains:\n\n");

            while (rs.next()) {
                temp= rs.getString("username");	//the table has a field 'username'
                System.out.println(temp);
            }
            rs.close();
            System.out.println("\nSuccessfully connected to CSIL SQL Server!\n\n");
        }catch (SQLException se)
        {
            System.out.println("\nSQL Exception occurred, the state : "+
                    se.getSQLState()+"\nMessage:\n"+se.getMessage()+"\n");
            return;
        }
    }//end of main
}//end of class sample_java_jdbc_driver_for_sqlserver
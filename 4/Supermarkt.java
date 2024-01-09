import java.io.*;
import java.sql.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class Supermarkt {
    static private Connection con;
    static Scanner scanner = new Scanner(System.in);

   public Supermarkt() throws ClassNotFoundException, FileNotFoundException,
                                   IOException, SQLException {
   }

   public void alleWaren () throws Exception{
       String query = "SELECT bezeichnung, preis, vorrat, kname FROM ware, kategorie";
       Statement  stmt = con.createStatement();
       ResultSet rs = stmt.executeQuery(query);

       System.out.println(String.format("%s %12s %11s %10s", "Bezeichnung", "Preis", "Vorrat", "Kategorie"));
       while (rs.next()) {
           System.out.println(String.format("%s %8.2f %7d %20s", 
                       rs.getString("bezeichnung"),
                       rs.getFloat("preis"),
                       rs.getInt("vorrat"),
                       rs.getString("kname")
                       ));
       }

       rs.close();
       stmt.close();
   }

   public void alleBestellungen() throws Exception {
        PreparedStatement pstmt = con.prepareStatement("SELECT bestid, datum, status, kname FROM bestellung JOIN kunde ON kundid = kundeid WHERE kname = ?");
        String kunde;

        while (true) {
            System.out.println("Kundenname: ");

            kunde = scanner.nextLine();
            if (kunde.isEmpty() || kunde.isBlank() || kunde.equals("#")) {
                break;
            }

            pstmt.setString(1, kunde);
            ResultSet rs = pstmt.executeQuery();

            try {
                System.out.println(String.format("%s %6s %12s %5s", "Best. ID", "Datum", "Status", "Name"));
                    while(rs.next()) {
                        System.out.println(String.format("%d %17s %3s %20s",
                                    rs.getInt("bestid"),
                                    rs.getString("datum"),
                                    rs.getString("status"),
                                    rs.getString("kname")
                                    ));
                    }
            }
            catch (Exception e) {
                System.out.println("Keine Bestellungen gefunden!");
            }
        }
   }

   public void bestellen() throws Exception {
        PreparedStatement bestellungStmt = con.prepareStatement("INSERT INTO bestellung(bestid, status, datum, kundid) VALUES (nextval(\'bestellid\'), ?, ?, ?)");
        PreparedStatement enthaeltStmt = con.prepareStatement("INSERT INTO enthaelt(bestid, warenid, anzahl) VALUES (currval(\'bestellid\'), ?, ?)");
        Statement stmt = con.createStatement();

        String kunde, ware;
        int kundeID;
        List<Integer> anzahl = new ArrayList<Integer>();
        List<Integer> wareID = new ArrayList<Integer>();

        System.out.println("Kundenname eingeben: ");
        kunde = scanner.nextLine();

        if(kunde.isEmpty() || kunde.isBlank() || kunde.equals("#")) {
            return;
        }

        ResultSet rs = stmt.executeQuery(String.format("SELECT kundeid FROM kunde WHERE kname = \'%s\'", kunde));
        try {
            rs.next() ;
            kundeID = rs.getInt("kundeid");
        }
        catch (Exception e) {
            // System.out.println(e.getMessage());
            System.out.println("Kunde wurde nicht gefunden!");

            rs.close();
            return;
        }
        rs.close();

        while (true) {
            System.out.println("Warenname eingeben: ");
            ware = scanner.nextLine();

            if (ware.isEmpty() || ware.isBlank() || ware.equals("#")) {
                break;
            }

            rs = stmt.executeQuery(String.format("SELECT warenid FROM ware WHERE bezeichnung = \'%s\'", ware));
            try {
                rs.next();
                wareID.add(rs.getInt("warenid"));
            }
            catch (Exception e) {
                // System.out.println(e.getMessage());
                System.out.println("Ware wurde nicht gefunden!");
                continue;
            }

            System.out.println("Anzahl eingeben: ");
            anzahl.add(scanner.nextInt());

            scanner.nextLine();
        }

        bestellungStmt.setString(1, "0");
        bestellungStmt.setDate(2, new java.sql.Date(System.currentTimeMillis()));
        bestellungStmt.setInt(3, kundeID);
        bestellungStmt.executeUpdate();

        for (int k = 0; k < wareID.size(); k++) {
            enthaeltStmt.setInt(1, wareID.get(k));
            enthaeltStmt.setInt(2, anzahl.get(k));
            enthaeltStmt.executeUpdate();
        }

        stmt.close();
        bestellungStmt.close();
   }

   public static void main (String args[]) throws IOException {
	if (args.length != 0) {
		System.out.println ("Usage: java supermarkt");
		System. exit(1);
	}
	String driverClass = "org.postgresql.Driver";
	try {
		Class.forName (driverClass);
	} catch (ClassNotFoundException exc) {
		System.out.println ("ClassNotFoundException: " + exc.getMessage() );
	}
      try {
	Class.forName ("org.postgresql.Driver");
	String db_url = "jdbc:postgresql://127.0.0.1:5432/wjsupermarkt";
	con = DriverManager.getConnection (db_url, "postgres", "password");
	Supermarkt sup = new Supermarkt();
	String aufgabe = null;
	BufferedReader userin
	     = new BufferedReader (new InputStreamReader (System.in));
	System.out.println
	     ("\nGeben Sie ein: Waren oder Bestellungen oder Bestellen oder #!\n");
	while ( ! (aufgabe =userin.readLine()).startsWith("#")) {
		if (aufgabe.equals ("Waren")) sup.alleWaren();
		else if (aufgabe.equals("Bestellungen")) sup.alleBestellungen();
		else if (aufgabe.equals("Bestellen")) sup.bestellen();
		System.out.println
			("\nGeben Sie ein: Waren oder Bestellungen oder Bestellen oder #!\n");
	}
	con.close();
      } catch (Exception exc)
      {
         System.err.println ("Exception in Main. " + exc.getMessage());
	exc.printStackTrace();
      }
   }
}

import java.sql.*;

public class Problem2 {

    public static void main(String[] args) {
        try {
            Connection conn = Mysql.getConnection();
            // crate statement
            //Statement stmt = conn.createStatement();

            String sql = "INSERT INTO actor(first_name, last_name) "
                    + "VALUES ('Tran', 'Vinh');";

            Statement stmt = conn.createStatement();

            // insert 'actor'
            stmt.executeUpdate(sql, Statement.RETURN_GENERATED_KEYS);

            ResultSet rs = stmt.getGeneratedKeys();
            // show data
            while (rs.next()) {
                System.out.println("Generated key ID: " + rs.getInt(1));
            }

            // close connection
            conn.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
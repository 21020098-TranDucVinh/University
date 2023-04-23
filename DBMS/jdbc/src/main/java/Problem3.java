import java.sql.*;

public class Problem3 {
    private static void Problem1() {
        try {
            Connection conn = Mysql.getConnection();

            String sql = "SELECT f.*\n" +
                    "FROM film_actor fa\n" +
                    "JOIN film f ON f.film_id = fa.film_id\n" +
                    "WHERE fa.actor_id = ?;";

            // crate statement
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setInt(1, 2);
            // select 'actor'
            ResultSet rs = stmt.executeQuery();

            ResultSetMetaData metaData = rs.getMetaData();

            // Iterate over the columns
            for (int i = 1; i <= 4; i++) {
                String columnName = metaData.getColumnName(i);
                System.out.printf(columnName + "\t");
            }
            System.out.println();

            // show data
            while (rs.next()) {
                System.out.println(rs.getInt(1)
                        + "\t" + rs.getString(2)
                        + "\t" + rs.getString(3)
                        + "\t" + rs.getInt(4));
            }

            // close connection
            conn.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private static void Problem2() {
        try {
            Connection conn = Mysql.getConnection();

            String sql = "INSERT INTO actor(first_name, last_name) "
                    + "VALUES (?, ?)";

            PreparedStatement stmt = conn.prepareStatement(sql,
                    Statement.RETURN_GENERATED_KEYS);

            stmt.setString(1, "Tran");
            stmt.setString(2, "Duc Vinh");

            // insert 'actor'
            stmt.executeUpdate();

            ResultSet rs = stmt.getGeneratedKeys();
            // show data
            while (rs.next()) {
                System.out.println("Generated key: " + rs.getInt(1));
            }

            // close connection
            conn.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Problem1();
    }
}

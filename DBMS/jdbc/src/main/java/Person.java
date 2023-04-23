import com.google.gson.Gson;

public class Person {
    private String name;
    private int age;
    private String address;

    public Person(String name, int age, String address) {
        this.name = name;
        this.age = age;
        this.address = address;
    }

    public String toString() {
        return name + " - " + age + " - " + address;
    }

    public static void main(String[] args) {
        //Tạo đối tượng Gson
        Gson gson = new Gson();
        Person person = new Person("Trang", 5, "Bắc Giang");

        //Chuyển đổi từ Object sang JSON
        String result = gson.toJson(person);
        System.out.println(result);
    }
}
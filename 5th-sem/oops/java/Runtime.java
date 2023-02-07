import java.util.*;

class tester {

  public void Add(int a, int b) {
    System.out.println("Sum is :" + a + b);
  }

  public static void main(String[] args) {
    System.out.println("parent class");
  }
}

public class Runtime extends tester {

  public void display() {
    System.out.println("Display method of parent class");
  }

  public static void main(String[] args) {
    Runtime obj = new Runtime();
    obj.display();
    Runtime obj1 = new Runtime();
    obj1.display();
  }
}

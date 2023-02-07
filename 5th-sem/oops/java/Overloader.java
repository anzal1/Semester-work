import java.util.*;

public class Overloader {

  Overloader() {
    System.out.println("Constructor called");
  }

  Overloader(int a) {
    System.out.println("Constructor called with int");
  }

  Overloader(String a) {
    System.out.println("Constructor called with String");
  }
  

  public void sum(int a, int b) {
    System.out.println("Sum is " + (a + b));
  }

  public int sum(int a, int b, int c) {
    return a + b + c;
  }

  public static void main(String[] args) {
    Overloader obj = new Overloader();
    System.out.println("Main method");
    System.out.println("Sum using first function: ");
    obj.sum(1, 2);
    System.out.println("Sum is " + obj.sum(1, 2, 3));
  }
}

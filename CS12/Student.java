package cs12.list;

public class Student {
  private String name = "";
  private int age = 0;
  private String course = "";

  public Student(String name, int age, String course) {
    this.name = name;
    this.age = age;
    this.course = course;
  }

  public String getName() { return this.name; }
  public int getAge() { return this.age; }
  public String getCourse() { return this.course; }

  public void setName(String name) { this.name = name; }
  public void setAge(int age) { this.age = age; }
  public void setCourse(String course) { this.course = course; }

  public String toString() {
    return this.name + ", " + this.age + ", " + this.course + "\n";
  }

  public String toStringRaw() {
    return this.name + "\n" + this.age + "\n" + this.course + "\n";
  }
}

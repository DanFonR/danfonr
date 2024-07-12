import java.util.Scanner;

class Grade {
  private int numGrade;
  private String letterGrade;
  private float GPA;

  public Grade(int numGrade) throws IllegalArgumentException {
    if (numGrade < 0 || numGrade > 100)
      throw new IllegalArgumentException();
    this.numGrade = numGrade;
    convertLetterGrade();
    convertGPA();
  }
  
  public String showGrade(String option) {
    return (option.toLowerCase().equals("letter"))?
      this.letterGrade : String.format("%.1f", this.GPA);
  }

  private void convertLetterGrade() {
    int grade = this.numGrade;
    int units = grade % 10;

    if (grade < 60) {
      this.letterGrade = "F";
      return;
    }
    else if (grade >= 97) {
      this.letterGrade = "A+";
      return;
    }

    this.letterGrade = "" + (char)('A' + 9 - grade / 10);
    if (0 <= units && units <= 2) this.letterGrade += "-";
    else if (units >= 7) this.letterGrade += "+";
  }
  
  private void convertGPA() {
    if (this.numGrade < 60) {
      this.GPA = 0.0F;
      return;
    }
    else if (this.numGrade >= 97) {
      this.GPA = 4.0F;
      return;
    }

    float grade = this.numGrade / 10 - 6 + .7F;

    if (this.numGrade % 10 >= 7)
      grade += .6F;
    else if (this.numGrade % 10 >= 3)
      grade += (grade == 3.7F)? .2F : .3F;
    
    this.GPA = grade;
  }
}

public class Grading {
	public static void main(String[] args) {
		Grade grade;
		Scanner scan = new Scanner(System.in);
		String option, USAGrade;

		if (args.length == 2) {
		  try {
		    grade = new Grade(Integer.valueOf(args[0]));
		    option = args[1];
		  }
		  catch(NumberFormatException e) {
		    System.err.println("Please type a whole number");
		    return;
		  }
		  catch(Exception e) {
		    System.err.println(
		    "First argument must be a number and the second a word");
		    return;
		  }
		}
		else if (args.length == 1 || args.length > 2) {
		  System.err.println("Provide either 0 or 2 arguments");
		  return;
		}
		else {
		  System.out.print("Enter grade (0-100): ");

		  try {
		    int input = scan.nextInt();
		    grade = new Grade(input);
		  }
		  catch(IllegalArgumentException e) {
		    System.err.println("Grade must be between 0 and 100");
		    return;
		  }
		  catch(Exception e) {
		    System.err.println("Please type a whole number");
		    return;
		  }
		  try {
		    System.out.print("GPA or letter grade? ");
		    option = scan.next();
		  }
		  catch(Exception e) {
		    System.err.println("Something went wrong");
		    return;
  		}
  		finally {
  		  scan.close();
		  }
		}
    
    if (!(option.toLowerCase().matches("gpa|letter"))) {
		      System.err.println(
		      "Invalid option. Options are \"GPA\" and \"letter\"");
		      return;
    }

		USAGrade = grade.showGrade(option);
		String msg = ((USAGrade.startsWith("A")
		                          || USAGrade.startsWith("F"))? "an " : "a ")
		                          + USAGrade;
		
		System.out.println("You scored " + msg);
	}
}

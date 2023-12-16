package Day1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;

public class Trebuchet {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new FileReader("./Day1/input.txt"));
    long sum = 0;
    String line;
    int index = 1;
    while ((line = br.readLine()) != null) {
      System.out.print("Line " + index++ + ": ");
      sum += Trebuchet.getCalibration(line);
      System.out.println("Sum: " + sum);
    }
    br.close();
    System.out.println("Calculated Sum is: " + sum);
  }

  private static String getNumericalString(String line) {
    StringBuilder sb = new StringBuilder();
    TrebuchetCharChecker checker = new TrebuchetCharChecker();
    for (int i = 0; i < line.length(); i++) {
      char character = line.charAt(i);
      if (character >= '0' && character <= '9') {
        sb.append(character);
      }

      int result = checker.next(character);
      if (result >= 0) {
        sb.append(result);
      }
    }
    return sb.toString();
  }

  public static int getCalibration(String line) {
    line = getNumericalString(line);
    System.out.print(line + " ");
    if (line.length() <= 0) {
      return 0;
    }
    return (line.charAt(0) - '0') * 10 + (line.charAt(line.length() - 1) - '0');
  }
}

class TrebuchetCharChecker {
  private HashMap<String, Integer> map;

  public TrebuchetCharChecker() {
    map = new HashMap<>(10);
    map.put("zero", 0);
    map.put("one", 0);
    map.put("two", 0);
    map.put("three", 0);
    map.put("four", 0);
    map.put("five", 0);
    map.put("six", 0);
    map.put("seven", 0);
    map.put("eight", 0);
    map.put("nine", 0);
  }

  public int next(char nextChar) {
    int result = -1;
    for (String key : map.keySet()) {
      int matchedChars = map.get(key);
      if (key.charAt(matchedChars) == nextChar) {
        matchedChars += 1;
        if (matchedChars == key.length()) {
          result = this.numberFromString(key);
          matchedChars = 0;
        }
      } else {
        matchedChars = key.charAt(0) == nextChar ? 1 : 0;
      }
      map.replace(key, matchedChars);
    }
    return result;
  }

  public int numberFromString(String str) {
    switch (str) {
      case "zero":
        return 0;
      case "one":
        return 1;
      case "two":
        return 2;
      case "three":
        return 3;
      case "four":
        return 4;
      case "five":
        return 5;
      case "six":
        return 6;
      case "seven":
        return 7;
      case "eight":
        return 8;
      case "nine":
        return 9;
      default:
        return -1;
    }
  }
}

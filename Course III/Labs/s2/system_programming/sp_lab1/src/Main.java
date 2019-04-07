import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

class Main
{
    public static void main(String[] args)
    {
        String pathname = "text.txt";
        try
        {
            Scanner fileScanner = getConfiguredScanner(pathname);
            Set<String> maximalLengthWords = findMaxLenWords(fileScanner);
            fileScanner.close();
            System.out.println("Maximal length words:");
            printStringSet(maximalLengthWords, "\t");
        }
        catch (FileNotFoundException e)
        {
            System.out.format("Could not find file '%s'.%n", pathname);
            System.exit(1);
        }
    }

    private static Scanner getConfiguredScanner(String pathname) throws FileNotFoundException
    {
        File file = new File(pathname);

        if (!file.exists()) {
            System.out.format("File '%s' does not exist.%n", pathname);
            System.exit(3);
        }

        if (!file.canRead()) {
            System.out.format("Cannot read file '%s'.%n", pathname);
            System.exit(2);
        }

        Scanner fileScanner = new Scanner(file);
        fileScanner.useDelimiter("[^a-zA-Z]+");

        return fileScanner;
    }

    private static Set<String> findMaxLenWords(Scanner scanner)
    {
        int maxLength = 0;
        String currentWord;
        Set<String> maxLengthWords = new HashSet<>();

        while (scanner.hasNext())
        {
            currentWord = scanner.next();

            // Add to split words longer than 30 characters!!!

            if (currentWord.length() > maxLength)
            {
                maxLength = currentWord.length();
                maxLengthWords.clear();
                maxLengthWords.add(currentWord);
            }
            else if (currentWord.length() == maxLength)
            {
                maxLengthWords.add(currentWord);
            }
        }

        return maxLengthWords;
    }

    private static void printStringSet(Set<String> ss, String indent)
    {
        for (String s: ss)
        {
            System.out.println(indent + s);
        }
    }
}
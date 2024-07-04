import java.util.Scanner;

public class Bubble_sort1 {
    public static void main(String[] args) {
        int temp = 0;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the size of array: ");
        int size = sc.nextInt();
        int[] arr = new int[size];
        for(int i=0; i<size; i++){
            System.out.println("Enter number "+i+":");
            arr[i]=sc.nextInt();
        }
        System.out.println("Unsorted array is");
        for(int i=0; i<size; i++){
            System.out.print(arr[i]+" ");
        }
        System.out.println();
        for(int i=0; i<size; i++){
            for(int j = 0; j<size-i-1; j++){
                if(arr[j]>arr[j+1]){
                    temp = arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
        }
        System.out.println("Sorted array is");
        for(int i=0; i<size; i++){
            System.out.print(arr[i]+" ");
        }

    }    
}

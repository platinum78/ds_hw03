# Programming Assignment #03 - Union of Two Binary Search Trees
Data Structures #41, School of Software, SKKU <br>
Susung Park (2014311254), School of Mechanical Engineering, SKKU

<br>

## 1. How to Use

To compile the program, simply move the terminal into the project directory, and then type `gcc main.c -o main.exe` . <br>
After compilation, type `./main.exe` to actually execute the program. Input file should have the name `input.txt` , and should be placed inside the `{PROJECT_DIR}/io` directory.

<br>

## 2. Algorithms

For the reading operation, the program first reads the text file line-by-line, and uses `sscanf()` function to parse the numbers at each line. Since the `sscanf()` function returns the numbers of tokens successfully read, this can be an indicator whether the line was about a normal edge or the root of a tree.

After the reading operation, the program tries to merge two BSTs. However, there were no possible algorithm to generally unify two BSTs into one, except the one iterating the smaller BST and inserting each node into the larger BST (at least within the range I've learned).

In the PDF file provided, there is a binary search tree, which is in an extremely special case; simply connecting the second BST as the left child of 18 of first BST is enough. This is possible because the rightmost of left subtree of 5 has smaller key than the leftmost of second BST. This allows the two BSTs to be merged into one with only single operation. However, in the following figure, it is not the case.

As shown in the figure, the values are 'coupled', so that simply moving one BST beneath the other is impossible. Perhaps the method of determining the range of keys by each subtree and moving in units of them could be possible, but that also causes large amount of computation, and the algorithm becomes complicated.

Therefore, in this assignment, the algorithm simply iterating through the smaller BST and then add each node into the first BST was used.

<br>

## 3. Time Complexity of the Algorithm

Since there was no repetitive instructions during the reading operation, the time complexity of reading operation can be considered as O(l), having l as the length of the text file.

For the merging operation, each element requires independent time for insertion operation. Therefore, the expected time complexity of merging operation is O(nlog(m)), having m as the number of nodes of the larger BST and n that of smaller BST.

<br>

## 4. Notes

This part will be written in Korean, for clearer delivery.

1. 과제 PDF 파일에는 Input 파일의 숫자가 u, v 이면 u가 상위 노드, v가 자식 노드인 것으로 표시되어 있으나, iCampus Q&A에서는 교수님께서 순서가 없는 것으로 언급하셨습니다. 이 과제에서는 과제 PDF의 내용을 따랐습니다.
2. 자료실에 업로드된 Input 파일이 올바르지 않습니다. 1번 파일 중 첫 번째 BST의 경우, Root Node는 10으로 정의되어 있으나 자식 노드들과의 관계가 정의되어 있지 않으며 (10, 17 라인이 있어야 합니다), 이 관계가 정의되어 있다고 하더라도 1 노드는 17노드의 하위가 아니라 Root Node인 10 노드의 하위에 들어가야 합니다. 두 번째 입력의 경우, 13은 이미 Root Node로 정의되어 있으나, 마지막 줄에서 19 노드의 하위에 삽입되는 관계가 중복 정의되어 있고, 이는 (적어도 지금까지 배운) BST의 제약 조건과 과제의 유일성 조건에 모두 어긋납니다.
3. 
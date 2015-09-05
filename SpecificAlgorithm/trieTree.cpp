
//功能：统计一段英文的单词频率(文章以空格分隔，没有标点) 
//思路：trie节点保存单词频率，然后通过DFS按字典序输出词频 
//时空复杂度: O(n*len)(len为单词平均长度)
//copyright@yansha 2011.10.25
//updated@July 2011.10.26
//程序尚不完善，有很多地方还需改进。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define num_of_letters 26
#define max_word_length 20

// 定义trie树节点
struct Trie   
{   
  int count;   
  Trie *next[num_of_letters]; 
};   

// 定义根节点 
Trie *root = NULL;

/**
* 建立trie树，同时保存单词频率
*/
void create_trie(char *word)
{
  int len = strlen(word);
  Trie *cur = root, *node;
  int pos = 0;

  // 深度为单词长度
  for(int i = 0; i < len; ++i)
  {
    // 将字母范围映射到0-25之间
    pos = word[i] - 'a';

    // 如果当前字母没有对应的trie树节点则建立，否则处理下一个字母
    if(cur->next[pos] == NULL)   //1、这里应该有个查找过程
    {
      node = (Trie *)malloc(sizeof(Trie));
      node->count = 0;

      // 初始化next节点
      for(int j = 0; j < num_of_letters; ++j)
      node->next[j] = NULL;

      // 开始处理下一个字母
      cur->next[pos] = node;
      }
  cur = cur->next[pos];
  }
  // 单词频率加1
  cur->count++;
}

/**
* 大写字母转化成小写字母
*/
void upper_to_lower(char *word, int len)
{
  for (int i = 0; i < len; ++i)
  {
    if(word[i] >= 'A' && word[i] <= 'Z')
    word[i] += 32;
  }
}

/**
* 处理输入
*/
void process_input()
{
  char word[max_word_length];

  // 打开统计文件(注意保持文件名一致)
  FILE *fp_passage = fopen("passage.txt", "r");  
  assert(fp_passage);

  // 循环处理单词
  while (fscanf(fp_passage, "%s", word) != EOF)  
  {  
    int len = strlen(word);  
    if (len > 0)  
      upper_to_lower(word, len);  
    create_trie(word);  
  }  
  fclose(fp_passage);  
}

/**
* 深度优先遍历
*/ 
void trie_dfs(Trie *p, char *queue)
{
  for(int i = 0; i < num_of_letters; ++i)
  {
    if(p->next[i] != NULL)
  {
    // 定义队列头结点
    char *head = queue;

    // 在末尾增加一个字母
    while (*queue != '\0')
      queue++;
    *queue = (char)(i + 'a');
    queue = head;

    // 在控制台打印单词及其频率
    if (p->next[i]->count > 0)
      printf("%s\t%d\n", queue, p->next[i]->count);

    trie_dfs(p->next[i], queue);

    // 在末尾去掉一个字母
    head = queue;
    while (*(queue+1) != '\0')
      queue++;
    *queue = '\0';
    queue = head;
    }
  }
}

int main()
{
  // 初始化trie树根节点
  root = (Trie *)malloc(sizeof(Trie));
  for(int j = 0; j < num_of_letters; ++j)
  root->next[j] = NULL;

  // 处理输入
  process_input();

  // 分配一个保存单词中间结果的队列
  char *queue = (char*) calloc(max_word_length, sizeof(char));

  // 通过DFS打印结果
  trie_dfs(root, queue);
  system("pause");
  return 0;
}
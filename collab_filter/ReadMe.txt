##############################
## 协同过滤推荐模块         ##
##############################


1. Introduction
    采用 Mahout 架构，对于场景三提供推荐。发现用户 A 和 B 都经常去某足球场，都是足球爱好者，如果 A 购买了近期某场足球比赛门票，则也协同推荐给 B。

2. Usage
The input should be "item preference" pair, and at most it can accept 3 pairs. In the following example, "20590" is item id and "3.0" is its preference.The output is the "item preference" pair in string, and at most it could ouput 3 pairs.

Example:

char* input = "20590 3.0 98925 5.0 8587 2.0";
char* output = 0;

output = collab_filter(input);
printf("Result of collab_filter: %s\n", output);

Output:

Result of collab_filter: [RecommendedItem[item:121859, value:10.0], RecommendedItem[item:101384, value:10.0], RecommendedItem[item:66445, value:10.0]]

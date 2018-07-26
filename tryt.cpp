class Solution:
def longestWord(self, words):
    """
    :type words: List[str]
    :rtype: str
    """
    
    words.sort()
    r = words
    r.reverse()
    flag = True
    w_list = []
    for word in r:
        for i in range(1, len(word)):
            if word[:i] not in words:
                flag = False
                break
            if flag == True:
                if len(w_list) > 1:
                    if len(w_list[-1]) <= len(word):
                        w_list.append(word)
                else:
                    w_list.append(word)
    if len(w_list) > 0:
        w_list.sort()
        return w_list[-1]
    else:
        return ""
            
        
    
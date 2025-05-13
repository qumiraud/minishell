/*


clear && make && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell




test de mon lien git sur mon pc fixe


ihdghuigd rgdhui hui rgdzhui rgdho rgzphio srgeho srg         jh sgjosgd fgd


s Fgdrg g drg dthsthxfth

('"'") <- SEGFAULT

""""

"""

""""'

"ghchc""jhhv"jhk'khgyj'











*/




/*

make: Nothing to be done for 'all'.
==63995== Memcheck, a memory error detector
==63995== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==63995== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==63995== Command: ./minishell
==63995== 
💾 minishell :awd ">" awd

glt_word : 3

1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
glutto_tab[0]: awd

glutto_tab[1]: ">"

glutto_tab[2]: awd

💾 minishell :awd ">>" awd

glt_word : 3

1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
count_l : 4
1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
glutto_tab[0]: awd

glutto_tab[1]: ">>"

glutto_tab[2]: awd

💾 minishell :awd ">>' awd
missing quote
💾 minishell :awd '>>' awd

glt_word : 3

1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
count_l : 4
1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
glutto_tab[0]: awd

glutto_tab[1]: '>>'

glutto_tab[2]: awd

💾 minishell :exit

glt_word : 1

1_word : 0
2_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 4
glutto_tab[0]: exit

exit
==63995== 
==63995== HEAP SUMMARY:
==63995==     in use at exit: 208,880 bytes in 244 blocks
==63995==   total heap usage: 588 allocs, 344 frees, 233,627 bytes allocated
==63995== 
==63995== 13 bytes in 1 blocks are definitely lost in loss record 7 of 76
==63995==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==63995==    by 0x48AFBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==63995==    by 0x488D694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==63995==    by 0x4897D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==63995==    by 0x4014AD: main (main.c:133)
==63995== 
==63995== LEAK SUMMARY:
==63995==    definitely lost: 13 bytes in 1 blocks
==63995==    indirectly lost: 0 bytes in 0 blocks
==63995==      possibly lost: 0 bytes in 0 blocks
==63995==    still reachable: 208,867 bytes in 243 blocks
==63995==         suppressed: 0 bytes in 0 blocks
==63995== Reachable blocks (those to which a pointer was found) are not shown.
==63995== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==63995== 
==63995== For lists of detected and suppressed errors, rerun with: -s
==63995== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)



*/

/**/


/**/


/**/


/**/


/**/


/**/


/**/

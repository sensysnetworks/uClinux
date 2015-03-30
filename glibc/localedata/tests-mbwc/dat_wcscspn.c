/*
 *  TEST SUITE FOR MB/WC FUNCTIONS IN C LIBRARY
 *
 *	 FILE:	dat_wcscspn.c
 *
 *	 WCSCSPN:  size_t wcscspn (const wchar_t *ws1, const wchar_t *ws2);
 */


TST_WCSCSPN tst_wcscspn_loc [] = {

    {	{ Twcscspn, TST_LOC_de },
	{
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 { 0x00D1,0x0000	       }, },  /* #1 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 {	  0x00D2,0x0000	       }, },  /* #2 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 {		 0x00D3,0x0000 }, },  /* #3 */
	    /*expect*/ { 0,1,2,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 {	  0x00D2,0x00D3,0x0000 }, },  /* #4 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 { 0x00D2,0x00D3,0x00D4,0x0000 }, },  /* #5 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 { 0x00D3,0x00D4,0x00D5,0x0000 }, },  /* #6 */
	    /*expect*/ { 0,1,2,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 { 0x00D1,0x00D2,0x00D3,0x0000 }, },  /* #7 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x0000,0x00D2,0x00D3,0x0000 },
			 { 0x00D2,0x000		       }, },  /* #8 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x00D3,0x0000 },
			 { 0x0000,0x00D2,0x00D3,0x0000 }, },  /* #9 */
	    /*expect*/ { 0,1,3,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x0000	       },
			 { 0x00D1,0x00D2,0x00D3,0x0000 }, },  /* #10 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x00D1,0x00D2,0x0000	       },
			 { 0x00D1,0x00D3,0x00D4,0x0000 }, },  /* #11 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { is_last: 1 }
	}
    },
    {	{ Twcscspn, TST_LOC_enUS },
	{
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 { 0x0041,0x0000	       }, },  /* #1 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 {	  0x0042,0x0000	       }, },  /* #2 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 {		 0x0043,0x0000 }, },  /* #3 */
	    /*expect*/ { 0,1,2,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 {	  0x0042,0x0043,0x0000 }, },  /* #4 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 { 0x0042,0x0043,0x0044,0x0000 }, },  /* #5 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 { 0x0043,0x0044,0x0045,0x0000 }, },  /* #6 */
	    /*expect*/ { 0,1,2,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 { 0x0041,0x0042,0x0043,0x0000 }, },  /* #7 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x0000,0x0042,0x0043,0x0000 },
			 { 0x0042,0x000		       }, },  /* #8 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0043,0x0000 },
			 { 0x0000,0x0042,0x0043,0x0000 }, },  /* #9 */
	    /*expect*/ { 0,1,3,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0000	       },
			 { 0x0041,0x0042,0x0043,0x0000 }, },  /* #10 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x0041,0x0042,0x0000	       },
			 { 0x0041,0x0043,0x0044,0x0000 }, },  /* #11 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { is_last: 1 }
	}
    },
    {	{ Twcscspn, TST_LOC_eucJP },
	{
	  { /*input.*/ { { 0x3041,0x3042,0x0043,0x0000 },
			 { 0x3041,0x0000	       }, },  /* #1 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x0043,0x0000 },
			 {	  0x3042,0x0000	       }, },  /* #2 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x3043,0x0000 },
			 {		 0x3043,0x0000 }, },  /* #3 */
	    /*expect*/ { 0,1,2,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x3043,0x0000 },
			 {	  0x3042,0x3043,0x0000 }, },  /* #4 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x3043,0x0000 },
			 { 0x3042,0x3043,0x3044,0x0000 }, },  /* #5 */
	    /*expect*/ { 0,1,1,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x3043,0x0000 },
			 { 0x3043,0x3044,0x3045,0x0000 }, },  /* #6 */
	    /*expect*/ { 0,1,2,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x3043,0x0000 },
			 { 0x3041,0x3042,0x3043,0x0000 }, },  /* #7 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x0000,0x3042,0x3043,0x0000 },
			 { 0x3042,0x0000	       }, },  /* #8 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x3043,0x0000 },
			 { 0x0000,0x3042,0x3043,0x0000 }, },  /* #9 */
	    /*expect*/ { 0,1,3,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x0000	       },
			 { 0x3041,0x3042,0x3043,0x0000 }, },  /* #10 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { /*input.*/ { { 0x3041,0x3042,0x0000	       },
			 { 0x3041,0x3043,0x3044,0x0000 }, },  /* #11 */
	    /*expect*/ { 0,1,0,			  },
	  },
	  { is_last: 1 }
	}
    },
    {	{ Twcscspn, TST_LOC_end }}
};

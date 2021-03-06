#
# This script was written by Renaud Deraison <deraison@cvs.nessus.org>
#
# See the Nessus Scripts License for details
#

if(description)
{
 script_id(11461);
 script_version ("$Revision: 1.1 $");
 script_bugtraq_id(1969);
 script_cve_id("CAN-2000-1161");
 

 name["english"] = "Adcycle Password Disclosure";
 
 script_name(english:name["english"]);
 
 desc["english"] = "
The CGI 'build.cgi' is installed. This CGI has
a well known security flaw that lets an attacker obtain 
the password of the remote AdCycle database or delete
databases.

Solution : remove it from /cgi-bin.

Risk factor : Serious";



 script_description(english:desc["english"]);
 
 summary["english"] = "Checks for the presence of /cgi-bin/build.cgi";
 
 script_summary(english:summary["english"], francais:summary["francais"]);
 
 script_category(ACT_GATHER_INFO);
 
 
 script_copyright(english:"This script is Copyright (C) 2003 Renaud Deraison",
		francais:"Ce script est Copyright (C) 2003 Renaud Deraison");
 family["english"] = "CGI abuses";
 family["francais"] = "Abus de CGI";
 script_family(english:family["english"], francais:family["francais"]);
 script_dependencie("find_service.nes", "no404.nasl");
 script_require_ports("Services/www", 80);
 exit(0);
}

#
# The script code starts here
#

include("http_func.inc");
include("http_keepalive.inc");


port = get_kb_item("Services/www");
if(!port) port = 80;
if(!get_port_state(port))exit(0);


foreach dir (cgi_dirs())
{
 res = is_cgi_installed_ka(item:string(dir, "/build.cgi"),
 		port:port);

 if( res == NULL ) exit (0);
 if( res != 0 ) { security_hole(port); exit(0); }
}

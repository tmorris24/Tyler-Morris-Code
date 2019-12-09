#include <stdio.h>
#include <math.h>
#define discount .05
#define tax .08

/* Student Assignment Submission Form
I declare that the attached assignment is wholly my own work in accordance with UCF
Academic Policy. No part of this assignment (except for this comment) has been copied manually or electronically
from any other source (including web sites) or distributed to other students.
My name is : Morris Tyler , Date: 02/25/2019 */

int main(){
	
	//Initialize Variables
	double total, web, email, net, IP, subtotal, bundle, subbundle, taxcost, finalcost;
	char choiceweb, choicemail, choicenet, choiceip;
	int webselect, emailselect, netselect, IPselect, packcount;
	
	//Welcome
	printf("Welcome to AMCD Hosting Inc. \n\n");
	
	//Web Hosting Prompt
	printf("Would you like to subscribe to Web Hosting Service? (Y or N)\n\n");
	scanf ("%c", &choiceweb);
	printf("\n");
	
	//Begin of Webpackage selection
	switch(choiceweb){
	
	case 'y':
	case 'Y':
		
		printf("Please choose a web hosting package \n [1] -Silver: $29.99/month \n - Unlimited Bandwidth \n - 1 Website Hosting \n - 1 GB Hard Drive Space \n \n [2] - Gold: $39.99/month \n - Unlimited Bandwidth \n - 5 Website Hosting \n - 10 GB Hard Drive Space \n \n [3] - Platinum: $49.99/month \n - Unlimited Bandwidth \n - 10 Website Hosting \n - 50 GB Hard Drive Space \n\n");
		scanf("%d", &webselect);
		printf("\n");
		
		//Switch statement for web hosting choice. 
		switch(webselect){
			case 1:
				web = 29.99;
				packcount++;
				break;
			
			case 2:
				web = 39.99;
				packcount++;
				break;
				
			case 3:
				web=49.99;
				packcount++;
				break;
			
			default:
				printf("No package was selected. Web hosting cost is $0. \n");
				web=0;	
				break;	
		}
		break;
	
	default:
		printf("Web Hosting will not be selected.\n");
		web=0;
		break;
	} 
	//End of web hosting
	
	//Begin of IP selection
	if (web!=0){
		while(IPselect<1 || IPselect>2){
			printf("Please select an IP type \n [1] - Shared IP - $2.99/moth \n\n [2] - Dedicated IP $6.99/month \n\n");
			scanf("%d",&IPselect);
			printf("\n");
		
			//Begin Switch statement for Ip selection
		
			switch(IPselect){
			
				case 1:
					IP=2.99;
					break;
			
				case 2:
					IP= 6.99;
					break;
				
				default:
					printf("You must pick a IP type!\n");
					printf("\n");
					IPselect=0;
					break;
			}
		}
	}
	
	//End of IP selection

	//Email Marketing Prompt
	printf("Would you like to subscribe to Email Marketing Service? (Y or N)\n\n");
	scanf(" %c", &choicemail);
	printf("\n");
	
	//Begin of Email Package selection
	switch(choicemail){
	
	case 'y':
	case 'Y':
		
		printf("Please choose an email market package. \n [1] - Economy: $19.99/month \n - Up to 1,000 subscribers \n - Unlimited emails \n \n [2] - Deluxe: $29.99/month \n -Up to 5,000 subscribers \n - Unlimited emails \n - Over 160 ready-made design \n \n [3] - Premium:$39.99/month\n - Up to 10,000 subscribers \n - Unlimited emails \n - Over 160 ready-made design\n\n");		
		scanf("%d", &emailselect);
		printf("\n");
		
		//Switch statement for Email Market choice. 
		switch(emailselect){
			case 1:
				email = 19.99;
				packcount++;
				break;
			
			case 2:
				email = 29.99;
				packcount++;
				break;
				
			case 3:
				email=39.99;
				packcount++;
				break;
			
			default:
				printf("No package was selected. Email Marketing cost is $0. \n");		
				printf("\n");
				email=0;	
				break;	
		}
		break;
	
	default:
		printf("Email Marketing will not be selected.\n\n");
		email=0;
		break;
	} 
	//End of EMail Marketing
	
	//Internet Marketing Prompt
	printf("Would you like to subscribe to Internet Marketing Service? (Y or N)\n\n");
	scanf(" %c", &choicenet);
	
	//Begin of Email Package selection
	switch(choicenet){
	
	case 'y':
	case 'Y':
		
		printf("\nPlease choose an internet marketing package. \n [1] - Basic: $59.99/month \n - Link Building (Organic SEO) \n - Video Marketing \n\n");		
		scanf("%d", &netselect);
		printf("\n");
		
		//Switch statement for Internet Market choice. 
		switch(netselect){
			case 1:
				net = 59.99;
				packcount++;
				break;
			
			case 2:
				net = 99.99;
				packcount++;
				break;
			
			default:
				printf("No package was selected. Internet Marketing cost is $0. \n\n");
				net=0;	
				break;	
		}
		break;
	
	default:
		printf("Internet Marketing will not be selected.\n\n");
		net=0;
		break;
	} 
	//End of Net Marketing	
	
	//Calculating and displaying total
	
	subtotal = web + net + email+ IP;
	subbundle=subtotal-bundle;
	taxcost= tax*subbundle;
	finalcost=subtotal+taxcost-bundle;
	
	
	if(packcount<1){
		bundle=0;	
	}
	else if(packcount>1){
		bundle=subtotal*discount;
	}
	
	//Displaying totals
	
	printf("\n\n\n---------------------------------------------------------------------------- \n");
	printf("AMCD HOSTING INC Bill Details \n");
	printf("---------------------------------------------------------------------------- \n");
	printf("Package Cost\t\t Package\t\t Cost\n");
	
	if(webselect= 1||2||3){
		printf("Web Hosting \t \t \t %d \t \t $%.2f \n", webselect, web);
	}
	if(IPselect = 1||2){
		printf("\t \t IP Services \t %d \t \t $%.2f \n",IPselect, IP);
	}
	if(emailselect = 1||2||3){
		printf("Email Marketing \t \t %d \t \t $%.2f \n", emailselect,email);
	}
	if(netselect = 1||2||3){
		printf("Internet Marketing \t \t %d \t \t $%.2f \n", netselect, net);
	}
	printf("Subtotal: \t\t\t\t\t $%.2f\n",subtotal);
	printf("Bundle Discount: \t\t %%5 \t\t $%.2f \n", bundle);
	printf("Total Before Tax: \t \t \t \t $%.2f \n",subbundle);
	printf("Tax: \t \t %%8 \t\t\t\t $%.2f \n",taxcost);
	printf("Amount due: \t\t\t\t\t $%.2f",finalcost);
}

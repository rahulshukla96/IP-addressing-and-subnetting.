package project.java;
import java.util.Scanner;

public class test2 
{
	private static final char Begin = 0;

	public static void main(String args[])
	{

		int oct1, oct2, oct3, oct4;
		int i, maxnh, maxsnw, db;
		Scanner in = new Scanner(System.in);

		System.out.println("Please fill in the details of the IP address-\n\n");
		System.out.println("First octate: ");
		oct1 = in.nextInt();

		for(i=0; i<=1000000; i++)
		{

			while(oct1<1 || oct1>255)
			{
				System.out.println("Invalid number entered! Kindly try again.\n");
				System.out.println("First octate: ");
				oct1 = in.nextInt();
			}
			while(oct1>223 && oct1<255)
			{
				System.out.println("You can't enter this number. Such IPs are reserved for government and research purposes. Kindly try again.\n");
				System.out.println("First octate: ");
				oct1 = in.nextInt();
			}
		}
		System.out.println("Second octate: ");
		oct2 = in.nextInt();
		while(oct2<0 || oct2>255)
		{
			System.out.println("Invalid number entered! Kindly try again.\n");
			System.out.println("Second octate: ");
			oct2 = in.nextInt();
		}
		System.out.println("Third octate: ");
		oct3 = in.nextInt();
		while(oct3<0 || oct3>255)
		{
			System.out.println("Invalid number entered! Kindly try again.\n");
			System.out.println("Third octate: ");
			oct3 = in.nextInt();
		}
		System.out.println("Fourth octate: ");
		oct4 = in.nextInt();
		while(oct4<0 || oct4>255)
		{
			System.out.println("Invalid number entered! Kindly try again.\n");
			System.out.println("Fourth octate: ");
			oct3 = in.nextInt();
		}

		System.out.println("\n\nThe entered IP address is " +oct1 +"." +oct2 +"." +oct3 +"." +oct4);

		if (oct1>=1 && oct1<=126)
		{
			System.out.println("This is class A IP address. Subnet mask= 255.0.0.0\n\n");
			maxnh = 8388607;
			maxsnw = 8388608;
			db = 24; //db is the default number of bits to be played with
			calcSHbits(maxnh, maxsnw, db, oct1, oct2, oct3);

			//calcRange(oct1);
		}
		else
		{
			if(oct1>=128 && oct1<=191)
			{
				System.out.println("This is class B IP address. Subnet mask= 255.255.0.0\n\n");
				maxnh = 32767;
				db = 16;
				maxsnw = 32768;
				calcSHbits(maxnh, maxsnw, db, oct1, oct2, oct3);

				//            calcRange(oct1);
			}
			else
			{
				System.out.println("This is class C IP address. Subnet mask= 255.255.255.0\n\n");
				maxnh = 126;
				db = 8;
				maxsnw = 128;
				calcSHbits(maxnh, maxsnw, db, oct1, oct2, oct3);

				//calcRange(oct1);
			}
		}

		// help(oct2, oct3);
	}

	public static void calcSHbits(int maxnh, int maxsnw,int db, int oct1, int oct2, int oct3)
	{
		int hpn, snw = 0, choice;
		float nhb, nsb;

		Scanner in2 = new Scanner(System.in);

		System.out.println("Kindly choose the preferred option(1 or 2) as per your network requirements: \n\n");
		System.out.println("1. If you want to subnet according to the number of hosts per network \n");
		System.out.println("2. If you want to subnet according to the number of sub-networks \n");
		choice = in2.nextInt();

		while (choice != 1 && choice != 2)
		{
			System.out.println("Invalid choice entered. Try again !");
			choice = in2.nextInt();
		}

		if(choice == 1)
		{
			System.out.println("Enter the required number of hosts per sub-network- ");
			hpn = in2.nextInt();

			while(hpn > maxnh)
			{
				System.out.println("Entered number of hosts exceed the maximum number of hosts per network. Try again.\n");
				System.out.println("Enter the required number of hosts per network- ");
				hpn = in2.nextInt();
			}

			/*for(i = 0; i<= 1000; i ++)
        {
            if(hpn == pow(2,i) || hpn == pow(2,i)-1)
            {
                hpn = pow(2, i)+1;
            }
        }*/

			nhb = (float) (Math.log(hpn+2)/Math.log(2));
			System.out.println("Number of host bits after subnetting= %.0f\n" +Math.ceil(nhb));
			int store = (int) Math.ceil(nhb);
			System.out.println("Number of IPs that can be assigned to hosts(Number of valid hosts) per network " +(Math.pow(2, store)-2));

			int store2 = (int) (Math.pow(2, store)-2);

			if(store2>512)
			{
				System.out.println("\nSuggestion 1\n");
				System.out.println("\nWe'd like to point out that number of hosts per network from this network configuration is not recommended. It jams the network with traffic.\n");
				System.out.println("\nTo avoid, kindly do not go for any more than 512 hosts per network.\n\n");
			}

			System.out.println("\nNumber of subnet bits = " +(db-store));
			System.out.println("\nNumber of sub-networks= " +Math.pow(2, db-store));



			float var1 = store;
			float var2 = db-store;

			calcNSM(db, choice, snw, var1, var2, oct1, oct2, oct3);
		}

		if(choice == 2)
		{
			System.out.println("Enter the required number of total sub-networks- ");
			snw = in2.nextInt();


			while(snw > maxsnw)
			{
				System.out.println("Entered number of subnets exceeds the maximum number of sub-networks possible. Try again.\n");
				System.out.println("Enter the required number of total sub-networks- ");
				snw = in2.nextInt();
			}

			nsb = (float) (Math.log(snw)/Math.log(2));

			System.out.println("Number of subnet bits = %.0f\n" +Math.ceil(nsb));
			int store3 = (int) Math.ceil(nsb);

			System.out.println("Number of sub-networks= %.0f\n\n" +Math.pow(2, store3));

			System.out.println("Number of host bits after subnetting= " +(db-store3));
			int store4 = db-store3;

			System.out.println("Number of IPs that can be assigned to hosts(Number of valid hosts per network) per network = " +(Math.pow(2, store4)-2));
			int store5 = (int) (Math.pow(2, store4)-2);

			if(store5 >512)
			{
				System.out.println("\nSuggestion 1\n");
				System.out.println("\nWe'd like to point out that number of hosts per network from this network configuration is not recommended. It jams the network with traffic.\n");
				System.out.println("To avoid, kindly do not go for any network configuration that allows more than 512 hosts per network.\n\n");
			}




			float var1 = store4;
			float var2 = store3;

			calcNSM(db, choice, snw, var1, var2, oct1, oct2, oct3);
		}
	}

	public static void calcNSM(float db, int choice, int snw, float var1, float var2, int oct1, int oct2, int oct3 )
	{
		int i, inc = 0, incOct = 0, a = 0;

		//for class C
		if(db == 8)
		{
			for(i = 7; i >= var1; i--)
			{
				a = a + (int) (Math.pow(2, i));
			}
			System.out.println("The new subnet mask is 255.255.255." +a);

			inc = (int) Math.pow(2, var1);
			incOct=4;
		}
		//for class B
		else if(db == 16 && var2 >=1 && var2 <=8)
		{
			for(i = 7; i >= (8-var2); i--)
			{
				a = a + (int) (Math.pow(2, i));
			}
			System.out.println("The new subnet mask is"+a);

			inc = (int) Math.pow(2, (8-var2));
			incOct=3;
		}

		else if(db == 16 && var2 >=9 && var2 <=15)
		{
			for(i=0; i < var2-8; i++)
			{
				a = a + (int) (Math.pow(2, (7-i)));
			}
			System.out.println("The new subnet mask is "+a);

			inc = (int) Math.pow(2, (16-var2));
			incOct= 4;
		}
		//for class A
		else if(db == 24 && var2 >=1 && var2 <=8)
		{
			for(i=7; i>=(8-var2); i--)
			{
				a = a + (int) (Math.pow(2,i));
			}
			System.out.println("The new subnet mask is "+a);

			inc = (int) Math.pow(2, (8-var2));
			incOct=2;
		}
		else if(db == 24 && var2 >= 9 && var2 <= 16)
		{
			for(i = 7; i >= (16-var2); i--)
			{
				a = a + (int) (Math.pow(2, i));
			}
			System.out.println("The new subnet mask is "+a);

			inc = (int) Math.pow(2, (16-var2));
			incOct= 3;
		}

		else if(db == 24 && var2 >= 17 && var2 <= 23)
		{
			for(i = 7; i >= (24-var2); i--)
			{
				a = a + (int) (Math.pow(2, i));
			}
			System.out.println("The new subnet mask is"+a);

			inc = (int) Math.pow(2, (24-var2));
			incOct= 4;
		}
		calcRange(snw, choice, oct1, oct2, oct3, inc, incOct);
	}
	public static void calcRange(int snw, int choice, int oct1, int oct2, int oct3, int inc, int incOct)
	{
		int i, j, k, nwb, rb, nwn, lnbp, inc2= 0; //nwb is NW bits and nwn is number of NWs, rb is rest bits.
		//int defaultbits;
		System.out.println("\n");


		if (oct1>=1 && oct1<=126)
		{
			System.out.println("The network ID/address of the entered address is-"+oct1 +"." +"." +".");
			System.out.println("The broadcast address of the entered address is- "+oct1 +"255" +"255" +"255");


			System.out.println("\nThe detail of sub-networks is as follows: \n\n");
			System.out.println(+oct1);


			if(incOct == 2)
			{
				for(i = 2; i <= ((256/inc)); i++ )
				{
					inc2 = inc2+inc;
					System.out.println( oct1+""+(inc2-1)+""+i);

					System.out.println( oct1+""+inc2);
				}
				System.out.println (+oct1);

			}



			else if(incOct == 3)
			{

				for(j = 0; j<256; j++)
				{
					System.out.println(oct1+""+j);

					inc2 = 0;

					for(i = 2; i <= ((256/inc)); i++ )
					{
						inc2 = inc2+inc;
						System.out.println(oct1+""+j+""+(inc2-1));

						System.out.println (oct1+""+j+""+inc2);

					}
					System.out.println(oct1+""+j);

				}
			}



			else
			{

				System.out.println(oct1+""+inc);

				for(k = 0; k<=255; k++)
				{

					for(j = 0; j<256; j++)
					{
						System.out.println(oct1+""+k+""+j);

						inc2 = 0;

						for(i = 2; i <= ((256/inc)); i++ )
						{
							inc2 = inc2+inc;

							System.out.println ( oct1 +"" +k+"" +j +""+ inc2);

						}
					}


				}
			}
		}

		//for class B
		else if (oct1>=128 && oct1<=191)
		{
			System.out.println("The network ID/address of the entered address is- %d.%d.0.0\n"+oct1+""+oct2);
			System.out.println("The broadcast address of the entered address is- %d.%d.255.255\n" +oct1+""+oct2);
			System.out.println("\nThe detail of sub-networks is as follows: \n\n");
			System.out.println("1. %d.%d.0.0    -    " +oct1+""+oct2);

			//dual testing done
			if(incOct == 3)
			{
				for(i = 2; i <= ((256/inc)); i++ )
				{

					inc2 = inc2+inc;

					System.out.println(oct1+""+oct2+""+(inc2-1));
					System.out.println(i +""+ oct1 +""+ oct2 +""+ inc2);
				}
				System.out.println(+oct1+oct2);
			}

			// dual testing done

			else
			{

				for(j = 0; j<256; j++)
				{
					System.out.println(oct1+""+oct2+""+j+""+10);
					inc2 = 0;

					for(i = 2; i <= ((256/inc)); i++ )
					{
						inc2 = inc2+inc;
						System.out.println(oct1+""+oct2+""+j+""+(inc2-1));
						System.out.println(oct1+""+oct2+""+j+""+inc2);

					}
					System.out.println(oct1+""+oct2+""+j);
				}
			}
		}


		else
		{
			System.out.println("\nThe network ID/address of the entered address is-" +oct1+""+oct2+""+oct3 );
			System.out.println("\nThe broadcast address of the entered address is- " +oct1+""+oct2+""+oct3);
			System.out.println("\nThe detalis of sub-networks is as follows: \n\n");
			System.out.println(oct1+""+oct2+""+oct3);

			for(i = 2; i <= ((256/inc)); i++ )
			{
				inc2 = inc2+inc;
				System.out.println(oct1+""+oct2+""+oct3+""+(inc2-1));
				System.out.println(i+""+oct1+""+oct2+""+oct3+""+inc2);
			}
			System.out.println(oct1+""+oct2+""+oct3);

		}
		if (choice ==1)
			System.out.println("\n\nYou can choose any number of networks from these ranges. All of them have equal number of hosts. \n\n");

		if(choice == 2)
			System.out.println("\n\nYou can choose any %d networks from this range. \n\n" +snw);

	}



	public static void  DisplayBegin(char chBegin)
	{

		Scanner in = new Scanner(System.in);
		chBegin = in.next().charAt(0);
		//printf("This project has two modules: First one deals with IP subnetting and supernetting.");
		//printf("Other one is for different but most common type of subnetting, which is Reverse Engineering Subnetting.\n\n");
		//printf("Choose 1 to enter first module and 2 to enter second module.");
		//scanf("%c", &chBegin);



		switch (chBegin)
		{
		case '1':
			System.out.println ("\n\n\tYou have now entered the module 1: IP Subnetting and Supernetting\n");
			break;
		case '2':
			System.out.println("\n\n\tYou have now entered the module 2: IP subnetting by Reverse Engineering\n");
			revEng();
			break;
		default :
			break;
		}


		if(chBegin != '1' && chBegin != '2')
		{

			System.out.println("\n\tInvalid choice. Wish you knew what are alphabets. \n");
			System.out.println("\tEnter either 1 or 2-");
			//scanf("%c",&chBegin);
			DisplayBegin(chBegin);
		}



	}


	public static void revEng()
	{
		int oct1, oct2, oct3, oct4;
		int i;
		char chBegin;
		Scanner in = new Scanner(System.in);
		chBegin =in.next().charAt(0);
		System.out.println("Please fill in the details of the IP address-\n\n");
		System.out.println("First octate: ");


		for(i=0; i<=1000000; i++)
		{

			while(oct1<1 || oct1>255)
			{
				System.out.println("Invalid number entered! Kindly try again.\n");
				System.out.println("First octate: ");
				// scanf("%i", &oct1);
				//Scanner in1 = new Scanner(System.in);
				oct1=in.nextInt();
			}
			
			while(oct1>223 && oct1<=255)
			{
				System.out.println("You can't enter this number. Such IPs are reserved for government and research purposes. Kindly try again.\n");
				System.out.println("First octate: ");
				//scanf("%i", &oct1);
				//Scanner in1 = new Scanner(System.in);
				oct1=in.nextInt();
			}
		}
		System.out.println("Second octate: ");
		//scanf("%i", &oct2);
		oct2=in.nextInt();

		while(oct2<0 || oct2>255)
		{
			System.out.println("Invalid number entered! Kindly try again.\n");
			System.out.println("Second octate: ");
			// scanf("%i", &oct2);
			oct2=in.nextInt();

		}
		System.out.println("Third octate: ");

		//scanf("%i", &oct3);
		oct3=in.nextInt();

		while(oct3<0 || oct3>255)
		{
			System.out.println("Invalid number entered! Kindly try again.\n");
			System.out.println("Third octate: ");
			oct3=in.nextInt();
		}
		System.out.println("Fourth octate: ");
		//scanf("%i", &oct4);
		oct3=in.nextInt();
		while(oct4<0 || oct4>255)
		{
			System.out.println("Invalid number entered! Kindly try again.\n");
			System.out.println("Fourth octate: ");
			//scanf("%i", &oct4);
			oct4=in.nextInt();
		}
		System.out.println("\n\nEntered IP address is %i.%i.%i.%i\n"+oct1+""+oct2+""+oct3+""+oct4);

		if (oct1>=1 && oct1<=126)
		{
			System.out.println("This is class A IP address. Default subnet mask= 255.0.0.0\n\n");
			//  validsmaskA();
		}
		else
		{
			if(oct1>=128 && oct1<=191)
			{
				System.out.println("This is class B IP address. Default subnet mask= 255.255.0.0\n\n");
				validsmaskB(oct1, oct2, oct3);

			}
			else
			{
				System.out.println("This is class C IP address. Default subnet mask= 255.255.255.0\n\n");
				validsmaskB(oct1, oct2, oct3);
			}
		}

	}

	public static void validsmaskB(int oct1, int oct2, int oct3)
	{


		int i, inc, incOct;
		int bitsBorrowed, snw, hpsnw, totalnwb;
		//char[] smaskb; 
		char[] smaskuser= new char[15];
		//char smaskuser2[15] = "\0";
		//smaskuser=new char[15];
		char smaskb11[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};

		//char smaskb11[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
		char smaskb12[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
		char smaskb13[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '0', '0', '\0', '\0'};
		char smaskb14[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
		char smaskb15[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '0', '\0', '\0'};
		char smaskb16[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '0', '0', '\0'};
		char smaskb17[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '\0', '\0'};
		char smaskb18[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '\0'};
		char smaskb19[] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '0'};

		char smaskb21[] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '\0', '\0'};
		char smaskb22[] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskb23[] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '0'};

		char smaskb31[] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '\0', '\0'};
		char smaskb32[] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskb33[] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '0'};

		char smaskb41[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '\0', '\0'};
		char smaskb42[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskb43[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '0'};

		char smaskb51[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '\0', '\0'};
		char smaskb52[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskb53[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '0'};

		char smaskb61[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '\0', '\0'};
		char smaskb62[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskb63[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '0'};

		char smaskb71[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '\0', '\0'};
		char smaskb72[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskb73[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '0'};

		char smaskb81[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '\0', '\0'};
		char smaskb82[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskb83[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '0'};


		char smaskc11[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0', '\0'};
		char smaskc12[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '\0'};
		//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
		char smaskc13[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0'};
		char smaskc2[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8'};
		char smaskc3[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2'};
		char smaskc4[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4'};
		char smaskc5[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0'};
		char smaskc6[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8'};
		char smaskc7[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2'};
		//char smaskc8[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4'};



		System.out.println("Enter the subnet mask which your network is to be masked with- ");
		System.out.println("\n\n\tNote: Only first 15 entered characters will be taken into account because that's all you need to enter a valid subnet mask address.\n");
		System.out.println("\n\n\tKindly enter no less or no more than 15 digits in your subnet mask.\n\n");
		System.out.println("Subnet mask: ");


		Scanner in = new Scanner(System.in) ;

		while (scanner.hasNext())
		{
			//Scanner scanner;
			char smaskuser = in.next().charAt(0);
		}
		System.out.println("Clean!");
		gets(smaskuser);




		for(i = 0; i < 15; i++)
		{
			char[] smaskuser;
			while(smaskuser[i] != smaskb11[i] && smaskuser[i] != smaskb12[i] && smaskuser[i] != smaskb13[i] &&  smaskuser[i] != smaskb14[i]
					&& smaskuser[i] != smaskb15[i] && smaskuser[i] != smaskb16[i] && smaskuser[i] != smaskb17[i] && smaskuser[i] != smaskb18[i] &&
					smaskuser[i] != smaskb19[i] &&
					smaskuser[i] != smaskb21[i] && smaskuser[i] != smaskb22[i] && smaskuser[i] != smaskb23[i] &&
					smaskuser[i] != smaskb31[i] && smaskuser[i] != smaskb32[i] && smaskuser[i] != smaskb33[i] &&
					smaskuser[i] != smaskb41[i] && smaskuser[i] != smaskb42[i] && smaskuser[i] != smaskb43[i] &&
					smaskuser[i] != smaskb51[i] && smaskuser[i] != smaskb52[i] && smaskuser[i] != smaskb53[i] &&
					smaskuser[i] != smaskb61[i] && smaskuser[i] != smaskb62[i] && smaskuser[i] != smaskb63[i] &&
					smaskuser[i] != smaskb71[i] && smaskuser[i] != smaskb72[i] && smaskuser[i] != smaskb73[i] &&
					smaskuser[i] != smaskb81[i] && smaskuser[i] != smaskb82[i] && smaskuser[i] != smaskb83[i] &&

					smaskuser[i] != smaskc11[i] && smaskuser[i] != smaskc12[i] && smaskuser[i] != smaskc13[i] &&smaskuser[i] != smaskc2[i]
							&&smaskuser[i] != smaskc3[i] && smaskuser[i] != smaskc4[i] &&smaskuser[i] != smaskc5[i] &&
							smaskuser[i] != smaskc6[i] && smaskuser[i] != smaskc7[i])
			{
				System.out.println("\nInvalid subnet mask entered! Try again.\n\t");
				//char smaskuser[15] = "\0";
				Scanner scanner = new Scanner(System.in);

				while (scanner.hasNext())
				{
					//Scanner scanner;
					char smaskuser11 = scanner.next().charAt(i);
				}
				System.out.println("Clean!");

				// fflush(stdin);
				//  gets(smaskuser);

				i = 0;
			}
		}



		if(smaskuser[8] == '0' && smaskuser[9] ==  '.' && smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
		{
			inc = 0 ; 
			incOct = 0;
			//printf("2sai h");
			System.out.println("The entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0;
			snw = 0;
			hpsnw = 65534;
			totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println(bitsBorrowed);
			System.out.println(totalnwb);
			System.out.println(snw);
			System.out.println(hpsnw);

			Object oct2;
			Object oct3;
			Object oct1;
			calcRange2(oct1, oct2, oct3, snw, inc, incOct);
		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '.' && smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0')

		{
			inc = 0;
			incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0;
			snw = 0; hpsnw = 65534;
			totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println(bitsBorrowed);
			System.out.println(totalnwb);
			System.out.println(snw);
			System.out.println(hpsnw);

			Object oct1;
			Object oct2;
			Object oct3;
			calcRange(oct1, oct2, oct3, snw, inc, incOct);

		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '.'  && smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0')
		{
			inc = 0;
			incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0;snw = 0; hpsnw = 65534; totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println(bitsBorrowed);
			System.out.println(totalnwb);
			System.out.println(snw);
			System.out.println(hpsnw);

			Object oct1;
			Object oct3;
			Object oct2;
			calcRange(oct1, oct2, oct3, snw, inc, incOct);

		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
		{
			inc = 0;
			incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0; snw = 0; hpsnw = 65534;totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println(bitsBorrowed);
			System.out.println(totalnwb);
			System.out.println(snw);
			System.out.println(hpsnw);

			Object oct2;
			Object oct1;
			Object oct3;
			calcRange2(oct1, oct2, oct3, snw, inc, incOct);
		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0')
		{
			inc = 0;
			incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0; snw = 0; hpsnw = 65534;totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println(bitsBorrowed);
			System.out.println(totalnwb);
			System.out.println(snw);
			System.out.println(hpsnw);

			Object oct1;
			Object oct2;
			Object oct3;
			calcRange2(oct1, oct2, oct3, snw, inc, incOct);
		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0')
		{
			inc = 0; incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0; snw = 0; hpsnw = 65534;totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
			System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
			System.out.println("The total number of subnetworks: %d\n\t"+snw);
			System.out.println("The total number of valid hosts per subnetwork" +hpsnw);

			Object oct3;
			Object oct1;
			Object oct2;
			calcRange2(oct1, oct2, oct3, snw, inc, incOct);
		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
		{
			inc = 0; incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0; snw = 0; hpsnw = 65534; totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println("The number of bits borrowed from host bits are : %d\n\t"+ bitsBorrowed);
			System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
			System.out.println("The total number of subnetworks: %d\n\t"+snw);
			System.out.println("The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

			Object oct1;
			Object oct2;
			Object oct3;
			calcRange2(oct1, oct2, oct3, snw, inc, incOct);
		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
		{
			inc = 0; incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0; snw = 0; hpsnw = 65534; totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
			System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
			System.out.println("The total number of subnetworks: %d\n\t"+snw);
			System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

			Object oct3;
			Object oct1;
			Object oct2;
			calcRange2(oct1, oct2, oct3, snw, inc, incOct);
		}
		else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
		{
			inc = 0; incOct = 0;
			//printf("2sai h");
			System.out.println("\nThe entered subnet mask is:  255.255.0.0");
			bitsBorrowed = 0; snw = 0;hpsnw = 65534; totalnwb = 16;
			System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
			System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
			System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
			System.out.println("The total number of subnetworks: %d\n\t"+snw);
			System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

			Object oct3;
			Object oct1;
			Object oct2;
			calcRange2(oct1, oct2, oct3, snw, inc, incOct);
		}


		else
		{
			Object oct3;
			Object oct1;
			Object oct2;
			char[] smaskuser;
			if(smaskuser[8] == '1' && smaskuser[9] ==  '2' && smaskuser[10] == '8' && smaskuser[12] == '0')
			{
				inc = 128;incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.128.0");
				bitsBorrowed = 1; snw = 2;hpsnw = 32766; totalnwb = 17;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '1' && smaskuser[9] ==  '9' && smaskuser[10] == '2' && smaskuser[12] == '0')
			{
				inc = 64; incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.192.0");
				bitsBorrowed = 2; snw = 4; hpsnw = 16382; totalnwb = 18;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

				calcRange(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '2' && smaskuser[10] == '4' && smaskuser[12] == '0')
			{
				inc = 32; incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.224.0");
				bitsBorrowed = 3; snw = 8; hpsnw = 8190; totalnwb = 19;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '4' && smaskuser[10] == '0' && smaskuser[12] == '0')
			{
				inc = 16; incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.240.0");
				bitsBorrowed = 4; snw = 16; hpsnw = 4094; totalnwb = 20;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '4' && smaskuser[10] == '8' && smaskuser[12] == '0')
			{
				inc = 8; incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.248.0");
				bitsBorrowed = 5; snw = 32; hpsnw = 2046; totalnwb = 21;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '2' && smaskuser[12] == '0')
			{
				inc = 4; incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.252.0");
				bitsBorrowed = 6; snw = 64; hpsnw = 1022; totalnwb = 22;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+ totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '4' && smaskuser[12] == '0')
			{
				inc = 2; incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.254.0");
				bitsBorrowed = 7; snw = 128; hpsnw = 510; totalnwb = 23;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+ bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+ totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[12] == '0')
			{
				inc = 1; incOct = 3;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.255.0");
				bitsBorrowed = 8; snw = 256; hpsnw = 254; totalnwb = 24;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+ bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+ snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
					smaskuser[12] == '1' && smaskuser[13] ==  '2' && smaskuser[14] == '8')
			{
				inc = 128; incOct = 4;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.255.128");
				bitsBorrowed = 9; snw = 512; hpsnw = 126; totalnwb = 25;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
					smaskuser[12] == '1' && smaskuser[13] ==  '9' && smaskuser[14] == '2')
			{
				inc = 64; incOct = 4;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.255.192");
				bitsBorrowed = 10; snw = 1024; hpsnw = 62; totalnwb = 26;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+ totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
					smaskuser[12] == '2' && smaskuser[13] ==  '2' && smaskuser[14] == '4')
			{
				inc = 32; incOct = 4;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.255.224");
				bitsBorrowed = 11;
				snw = 2048; hpsnw = 62;
				totalnwb = 27;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+ bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

				calcRange2( oct1,  oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
					smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '0')
			{
				inc = 16; incOct = 4;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.255.240\n");
				bitsBorrowed = 12; snw = 4096; hpsnw = 14; totalnwb = 28;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("2. Total number of network bits are: %d\n\t"+ totalnwb);
				System.out.println("3. The total number of subnetworks: %d\n\t"+snw);
				System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
					smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '8')
			{
				inc = 8;
				incOct = 4;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.255.248");
				bitsBorrowed = 13; snw = 8192;hpsnw = 6; totalnwb = 29;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+ totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				calcRange2(oct1, oct2, oct3, snw, inc, incOct);
			}

			else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
					smaskuser[12] == '2' && smaskuser[13] ==  '5' && smaskuser[14] == '2')
			{
				inc = 4; incOct = 4;
				//printf("2sai h");
				System.out.println("\nThe entered subnet mask is:  255.255.255.252");
				bitsBorrowed = 14;
				snw = 16384; hpsnw = 2; totalnwb = 30;
				System.out.println("\nA class B network with this subnet mask has following details:\n\t ");
				System.out.println("The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
				System.out.println("Total number of network bits are: %d\n\t"+totalnwb);
				System.out.println("The total number of subnetworks: %d\n\t"+snw);
				System.out.println("The total number of valid hosts per subnetwork: %d\n"+hpsnw);

				// Object object;
				calcRange2( oct1,  oct2,  oct3, snw, inc, incOct);
			}

			else{

				System.out.println("\n\n\tThe entered subnet mask is utterly stupid !\n\tRead a bit about subnet masks and come back later.\n");


			}
		}
	}


		public static void validsmaskC(int oct1, int oct2, int oct3)
		{
			int i, inc, incOct = 4;
			int bitsBorrowed, snw, hpsnw, totalnwb;
			char[] smasuser= new char[15];


			char smaskc11[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0', '\0'};
			char smaskc12[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '\0'};
			//char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
			char smaskc13[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0'};
			char smaskc2[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8'};
			char smaskc3[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2'};
			char smaskc4[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4'};
			char smaskc5[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0'};
			char smaskc6[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8'};
			char smaskc7[] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2'};
			//char smaskc8[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4'};

			System.out.println("\n\tEnter the subnet mask which your network is to be masked with-  \n\t");
			System.out.println("\n\n\tNote: Only first 15 entered characters will be taken into account because that's all you need to enter a valid subnet mask address.\n");
			System.out.println("\n\n\tKindly enter no less or no more than 15 digits in your subnet mask.\n\n");
			System.out.println("Subnet mask: ");

			// fflush(stdin);
			Scanner scanner = new Scanner(System.in) ;

			while (scanner.hasNext())
			{
				//Scanner scanner;
				char smaskuser = scanner.next().charAt(0);
			}
			System.out.println("Clean!");
			Object smaskuser;
			gets(smaskuser);

			for(i = 0; i < 15; i++)
			{
				char[] smaskuser;


				while(smaskuser[i]!= smaskc11[i] && smaskuser[i] != smaskc12[i] && smaskuser[i] != smaskc13[i] &&smaskuser[i] != smaskc2[i]
						&&smaskuser[i] != smaskc3[i] && smaskuser[i] != smaskc4[i] &&smaskuser[i] != smaskc5[i] &&
						smaskuser[i] != smaskc6[i] && smaskuser[i] != smaskc7[i])
				{

					System.out.println("\nInvalid subnet mask entered! Try again.\n\t");

					// fflush(stdin);
					// gets(smaskuser);
					Scanner scanner1 = new Scanner(System.in) ;

					while (scanner1.hasNext())
					{
						//Scanner scanner;
						char smaskuser = scanner1.next().charAt(0);
					}
					System.out.println("Clean!");
					Object smaskuser1;
					gets(smaskuser);

					i = 0;
				}




				if( smaskuser[15] == '0' )
				{
					inc = 256;
					//printf("1sai h");
					System.out.println("\n\nThe entered subnet mask is:  255.255.255.0\n\n");
					bitsBorrowed = 0; snw = 1; hpsnw = 254; totalnwb = 24;
					System.out.println("A class C network with this subnet mask has following details:\n\t ");
					System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+ bitsBorrowed);
					System.out.println("2. Total number of network bits are: %d\n\t"+ totalnwb);
					System.out.println("3. The total number of subnetworks: %d\n\t"+snw);
					System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

					calcRange2(oct1, oct2, oct3, snw, inc, incOct);
				}
				else if(smaskuser[12] == '1' && smaskuser[13] ==  '2' && smaskuser[14] == '8')
				{
					inc = 128;
					//printf("2sai h");
					System.out.println("\n\nThe entered subnet mask is:  255.255.255.128\n\n");
					bitsBorrowed = 1; snw = 2; hpsnw = 126; totalnwb = 25;
					System.out.println("A class C network with this subnet mask has following details:\n\t ");
					System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+ bitsBorrowed);
					System.out.println("2. Total number of network bits are: %d\n\t"+totalnwb);
					System.out.println("3. The total number of subnetworks: %d\n\t"+ snw);
					System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

					Object oct3;
					Object oct2;
					Object oct1;
					calcRange2(oct1, oct2, oct3, snw, inc, incOct);
				}

				else if(smaskuser[12] == '1' && smaskuser[13] ==  '9' && smaskuser[14] == '2')
				{
					inc = 64;
					//printf("3sai h");
					System.out.println("\n\nThe entered subnet mask is:  255.255.255.192\n\n");
					bitsBorrowed = 2; snw = 4; hpsnw = 62; totalnwb = 26;
					System.out.println("A class C network with this subnet mask has following details:\n\t ");
					System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+ bitsBorrowed);
					System.out.println("2. Total number of network bits are: %d\n\t"+ totalnwb);
					System.out.println("3. The total number of subnetworks: %d\n\t"+snw);
					System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

					calcRange2(oct1, oct2, oct3, snw, inc, incOct);
				}

				else if(smaskuser[12] == '2' && smaskuser[13] ==  '2' && smaskuser[14] == '4')
				{
					inc = 32;
					//printf("4sai h");
					System.out.println("\n\nThe entered subnet mask is:  255.255.255.224\n\n");
					bitsBorrowed = 3; snw = 8; hpsnw = 30; totalnwb = 27;
					System.out.println("A class C network with this subnet mask has following details:\n\t ");
					System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
					System.out.println("2. Total number of network bits are: %d\n\t"+ totalnwb);
					System.out.println("3. The total number of subnetworks: %d\n\t"+ snw);
					System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+ hpsnw);

					calcRange2(oct1, oct2, oct3, snw, inc, incOct);
				}

				else if(smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '0')
				{
					inc = 16;
					//printf("5sai h");
					System.out.println("\n\nThe entered subnet mask is:  255.255.255.240\n\n");
					bitsBorrowed = 4; snw = 16; hpsnw = 14; totalnwb = 28;
					System.out.println("A class C network with this subnet mask has following details:\n\t ");
					System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
					System.out.println("2. Total number of network bits are: %d\n\t"+ totalnwb);
					System.out.println("3. The total number of subnetworks: %d\n\t"+snw);
					System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+ hpsnw);


					calcRange2(oct1, oct2, oct3, snw, inc, incOct);
				}

				else if(smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '8')
				{
					inc = 8;
					//printf("6sai h");
					System.out.println("\n\nThe entered subnet mask is:  255.255.255.248\n\n");
					bitsBorrowed = 5; snw = 32; hpsnw = 6; totalnwb = 29;
					System.out.println("A class C network with this subnet mask has following details:\n\t ");
					System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
					System.out.println("2. Total number of network bits are: %d\n\t"+totalnwb);
					System.out.println("3. The total number of subnetworks: %d\n\t"+snw);
					System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+ hpsnw);


					calcRange2(oct1, oct2, oct3, snw, inc, incOct);
				}

				else if(smaskuser[12] == '2' && smaskuser[13] ==  '5' && smaskuser[14] == '2')
				{
					inc = 4;
					//printf("7sai h");
					printf("\n\nThe entered subnet mask is:  255.255.255.252\n\n");
					bitsBorrowed = 6; snw = 64; hpsnw = 2; totalnwb = 30;
					System.out.println("A class C network with this subnet mask has following details:\n\t ");
					System.out.println("1. The number of bits borrowed from host bits are : %d\n\t"+bitsBorrowed);
					System.out.println("2. Total number of network bits are: %d\n\t"+ totalnwb);
					System.out.println("3. The total number of subnetworks: %d\n\t"+snw);
					System.out.println("4. The total number of valid hosts per subnetwork: %d\n"+ hpsnw);



					calcRange2(oct1, oct2, oct3, snw, inc, incOct);
				}

				/*else if(smaskuser[12] == '2' && smaskuser[13] ==  '5' && smaskuser[14] == '4')
            {
                inc = 2;
                printf("8sai h");
                printf("The entered subnet mask is:  255.255.255.254");
            }*/

				else
				{
					printf("\n\n\tThe entered subnet mask is utterly stupid !\n\tRead a bit about subnet masks and come back later.\n");
				}



			}
		}


		private void gets(Object smaskuser) {
			// TODO Auto-generated method stub

		}

		private void printf(String string) {
			// TODO Auto-generated method stub

		}

		private void calcRange2(Object oct1, Object oct2, Object oct3, int snw2, int inc2, int incOct2) {
			// TODO Auto-generated method stub
		}


		int calcRange2(int oct1, int oct2, int oct3, int snw, int inc, int incOct)
		{
			int i, j, k, inc2 = 0;
			char ch;




			if (oct1>=128 && oct1<=191)   //means class B network
			{
				System.out.println("\nThe network ID/address of the entered address is- %d.%d.0.0\n"+oct1+""+ oct2);
				System.out.println("The broadcast address of the entered address is- %d.%d.255.255\n"+oct1+""+ oct2);

				System.out.println("\nThe above entered IP address with custom subnet mask lies in one of the following network ranges.\n\n ");
				System.out.println("\nPress any key to display all the %d networks below...\n\n"+snw);
				Object smaskuser;
				gets(smaskuser);

				System.out.println("\nThe detail of sub-networks is as follows: \n\n");
				System.out.println("1. %d.%d.0.0    -"+oct1+""+oct2);

				//dual testing done
				if(incOct == 3)
				{
					for(i = 2; i <= ((256/inc)); i++ )
					{
						//printf(" %d.%d.%d.255\n",  oct1, oct2, inc2-1);
						inc2 = inc2+inc;
						//printf("1. %d.%d.0.0\n",oct1, oct2);
						System.out.println(" %d.%d.%d.255\n"+oct1+""+oct2+"" +(inc2-1));
						System.out.println("%d. %d.%d.%d.0    -    "+i+""+oct1+""+oct2+""+ inc2);
					}
					System.out.println(" %d.%d.255.255\n"+oct1+"" +oct2);
				}

				// dual testing done
				//if(incOct == 4)
				else
				{
					//printf(" %d.%d.0.0\n",  oct1, oct2);
					//printf(" %d.%d.0.%d\n",  oct1, oct2, inc);

					for(j = 0; j<256; j++)
					{
						System.out.println(" %d.%d.%d.%d    -    "+oct1+""+ oct2+""+ j+""+ 0);
						inc2 = 0;

						for(i = 2; i <= ((256/inc)); i++ )
						{
							inc2 = inc2+inc;
							System.out.println(" %d.%d.%d.%d\n"+oct1+""+oct2+""+j+""+ (inc2-1));
							System.out.println(" %d.%d.%d.%d  "+oct1+""+oct2+""+j+""+inc2);

						}
						System.out.println(" %d.%d.%d.255\n"+  oct1+""+ oct2+""+ j);
					}
				}
			}






			if (oct1>=192 && oct1<=223)  //means class C network
			{
				System.out.println("\nThe network ID/address of the entered address is- %d.%d.%d.0\n"+oct1+""+ oct2+""+ oct3);
				System.out.println("The broadcast ID of the entered address is- %d.%d.%d.255\n"+oct1+""+ oct2+""+ oct3);

				System.out.println("\nThe above entered IP address with custom subnet mask lies in one of the following network ranges.\n\n ");
				System.out.println("\nPress any key to display all the %d networks below...\n\n"+snw);
				getClass();

				System.out.println("\nThe details of sub-networks for this subnet mask is as follows: \n\n");
				System.out.println("1. %d.%d.%d.0    -    "+oct1+""+ oct2+""+ oct3);

				for(i = 2; i <= ((256/inc)); i++ )
				{
					inc2 = inc2+inc;
					//inc3 = 1
					System.out.println(" %d.%d.%d.%d\n"+oct1+""+oct2+""+oct3+"" + (inc2-1));
					//printf("Valid host(IP) range in this network : %d.%d.%d.%d - %d.%d.%d.%d", oct1, oct2, oct3, inc2)
					System.out.println("%d. %d.%d.%d.%d    -    "+i+""+ oct1+""+oct2+""+oct3+""+ inc2);
				}
				System.out.println(" %d.%d.%d.255\n"+oct1+""+oct2+""+ oct3);

			}


		}
	}

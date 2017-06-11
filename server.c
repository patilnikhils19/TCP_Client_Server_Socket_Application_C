#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<pthread.h> 
#include<math.h> 
#include<time.h>

void *client_thread(void *);
int fibo(int number);
int ran(int high, int low);
 
int main(int argc , char *argv[])
{
    int socket_tcp , client_sock , c;
    struct sockaddr_in server , client;
     
    socket_tcp = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_tcp == -1)
    {
        printf("Error in creating socket\n");
    }
    puts("Socket sucessfully  created\n");
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 36000 );
     
    if( bind(socket_tcp,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("Socket binding failed\n");
        return 1;
    }
    puts("Socket binding completed\n");
     
    listen(socket_tcp , 5);
     
    puts("Accepting connections\n");
    c = sizeof(struct sockaddr_in);	
    
    pthread_t thread_number;
	
    while( (client_sock = accept(socket_tcp, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection recieved\n");
         
        if( pthread_create( &thread_number , NULL ,  client_thread , (void*) &client_sock) < 0)
        {
            printf("Problem in thread\n");
            return 1;
        }
	else{
	    puts("Thread Successfully Created for connection");
	}
	
    }
     
    if (client_sock < 0)
    {
        printf("Connection Failed\n");
        return 1;
    }
     
    return 0;
}
 
void *client_thread(void *socket_tcp)
{
    int connected = *(int*)socket_tcp;
    char send_data [4096] , recv_data[4096];
    int bytes_recieved, sin_size;
    printf("server is listening");
    FILE *fp;
    while ((bytes_recieved = recv(connected,recv_data,1024,0))>0)
            {
              printf("\nserver is listening\n");
              recv_data[bytes_recieved] = '\0';
              puts(recv_data);
              if (strcmp(recv_data , "exit") == 0 || strcmp(recv_data , "Exit") == 0)
             	{
	                fp = fopen("record.txt", "a+");
			fputs(recv_data,fp);
			fputs("\n",fp);
			fclose(fp);
			close(connected);
                	break;
              	}
              else if (strcmp(recv_data, "help")==0)
                {
			fp = fopen("record.txt", "a+");
                	fputs(recv_data,fp);
			fputs("\n",fp);
			char buffer[1024] = "You can use Following Commands : fibonacci 10 , random 5 17, sort 1 5 7 10, exit, help, show history";
                	send(connected, buffer,strlen(buffer), 0);

                }
              else if (strstr(recv_data, "fibonacci") != NULL)
                {
                	fp = fopen("record.txt", "a+");
			fputs(recv_data,fp);
			fputs("\n",fp);
			char * delimeter;
  			int array[10], i = 0;
			delimeter = strtok (recv_data," ");
			while (delimeter != NULL)
          		{
    				array[i] = atoi(delimeter);
    				delimeter = strtok (NULL, " ");
    				//printf("%d\n", array[i]);
    				i++;
  			}
			int result = fibo(array[1]);
                	char buffer[1024];
                	snprintf(buffer, 10, "%d", result);
			fputs(buffer, fp);
			fputs("\n",fp);
			fclose(fp);
                	send(connected, buffer,strlen(buffer), 0);
                }

              else if (strstr(recv_data, "random") != NULL)
                {
			fp = fopen("record.txt", "a+");
               		fputs(recv_data,fp);
			fputs("\n",fp);


                        char * delimeter;
                        int array[10], i = 0;
                        delimeter = strtok (recv_data," ");
                        while (delimeter != NULL)
                        {
                                array[i] = atoi(delimeter);
                                delimeter = strtok (NULL, " ");
                                //printf("%d\n", array[i]);
                                i++;
                        }
			int result = ran(array[1],array[2]+1);
                	char buffer[1024];
                	snprintf(buffer, 10, "%d", result);
                        fputs(buffer, fp);
			fputs("\n",fp);
                        fclose(fp);
                	send(connected, buffer,strlen(buffer), 0);
                }
              else if (strcmp(recv_data, "sort 1 5 7 10")==0)
                {
			fp = fopen("record.txt", "a+");
			fputs(recv_data,fp);
                	char buffer[1024] = "10 7 5 1";
                        fputs(buffer, fp);
			fputs("\n",fp);
                        fclose(fp);
                	send(connected, buffer,strlen(buffer), 0);
                }
	      else if (strcmp(recv_data, "show history")==0)
		{
			fp = fopen("record.txt", "a+");
			fputs(recv_data,fp);
			fputs("\n",fp);
                	char buffer[1024] = "show history Command";
                        fputs(buffer, fp);
			fputs("\n",fp);
                        fclose(fp);
			fp = fopen("record.txt", "r"); /* should check the result */
    			char line[256];
			while (fgets(line, sizeof(line), fp))
		        {
        			send(connected, line, strlen(line), 0); 
   			}
    			fclose(fp);
		}
              else
		{
                	char buffer[1024] = "Invalid Command";
                	send(connected, buffer,strlen(buffer), 0);
		}
	      fflush(stdout);
            }
    return 0;
}


int fibo(int number)
{
        int first = 0, second = 1, third = 0;
        if (number == 0)
        {
                return 0;
        }
        else if (number == 1)
        {
                return 1;
        }
        else
        {
                for(int i = 1; i<= number-2; i++)
                {
                        third = first + second;
                        first  = second;
                        second = third;
                }
                return third;
        }
}


int ran(int low, int high)
{
        int result;
	if(low == high){
	return low;
	}
	else if(low>high){
	high = high + low;
	low = high - low;
	high = high - low;
	}
	printf("%d and %d", high, low);
        srand(time(NULL));
        result = (rand() % (high- low)) + low;
        printf("Resulted random number = %d " , result);
        return result;
}


# 02-minitalk
The purpose of this project is to code a small data exchange program using UNIX signals.

Using only UNIX signals *SIGUSR1* and *SIGUSR2* the *client* can send text messages to the *server* process, which will then display the received text in the terminal.

The client sends each character of the message one bit at a time using the bit shift operator to extract each bit,
```c
if (c >> i & 1) // bit shifts to the right then looks at the right-most bit
			kill(pid, SIGUSR2); // SIGUSR2 = 1
		else
			kill(pid, SIGUSR1); // SIGUSR1 = 0
		wait_for_ack();
```

To avoid a "race condition" the server sends an acknowledge (ACK) signal after every bit received from the client. I used a small loop to wait for the the server's response. It waits up to 10,000 micro-seconds (probably longer when including execution time) before giving up and returning an error:
```c
void	wait_for_ack(void)
{
	int	t;

	t = 0;
	while (t++ < 10000)
	{
		if (g_server_ack)
			break ;
		usleep(1);
	}
}
```
*The `sigtimedwait()` function may have been useful here, but wasn't allowed in this project.

---

The server pieces together each character in the reverse order (i.e. shifting to the left), and prints each character once 8 bits have been received.
```c
c |= (signum == SIGUSR2); // bitwise-or will set the right-most bit to 1 if the received signal is SIGUSR2 (e.g. 0110 | 0001 = 0111)
	bits++;
	if (bits == 8) // check if a whole char has been received yet
	{
		write(1, &c, 1);
		bits = 0;
		c = 0;
	}
	else
		c <<= 1;
	kill(client_pid, SIGUSR2); // send ACK signal back to client
```

In testing I discovered that the si_pid variable delivered by the SA_SIGINFO flag would start out holding the pid of the client process, but would sometimes revert to 0, triggering an infinite loop. To avoid this I added this check to update the client pid only if it contains a valid value:
```c
if (info->si_pid != 0)
		client_pid = info->si_pid;
```
Compiling / Running
---

Run `make` in the root directory to compile the client and server.
Then use multiple terminal windows or a multiplexer like screen or tmux to start the server and send messages from the client.
![screenshot](../assets/minitalk-screenshot.png)

`make bonus` will compile a client with a few extra features (read from std input/directly from a text file).

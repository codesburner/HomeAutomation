using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

public class Daemon {
	
	private SerialConnection sc;
	private bool running;
	const byte DEBUG_LEVEL = 3;	//0, 1, 2, 3
	private TcpServer tcps;
	
	public Daemon(SerialConnection sc) {
		this.sc = sc;
		running = true;
	}
	
	public void stop () {
		running = false;
		Thread.Sleep(40);
		tcps.stop();
		
		// send a disconnect to avr? (call a function in serialconnection)
		
		//...för varje tcp-server...
	}
	
	public void addServer (TcpServer tcps) {
		//...lägg till servern i en lista...
		this.tcps = tcps;
		Thread t = new Thread(tcps.thread);
		t.Start();
	}
	
	public void thread() {
		CanPacket cp = null;
		while (running) {
			Thread.Sleep(1);
			bool hasMessage = sc.getPacket(out cp);
			if (hasMessage) {
				tcps.sendCanPacket(cp);
				
				if (DEBUG_LEVEL>2) { Console.WriteLine(">"+cp.toRawString()); }
			}
			
			string tcpdata;
			bool hasData = tcps.getData(out tcpdata);
			if (hasData) {
				if (tcpdata.Length>3) {
					//string canraw = tcpdata.Substring(4);
					cp = new CanPacket(tcpdata.Substring(4));
					//cp.setData(tcpdata.Substring(4));
					if (sc.writePacket(cp)) {
						if (DEBUG_LEVEL>2) { Console.WriteLine("<"+cp.toRawString()); }
					}
				}
			}
		}
	}
}

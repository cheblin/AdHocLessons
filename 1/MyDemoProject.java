package org.company.some_namespace;

import org.unirail.AdHoc.*;

public class MyDemoProject {}

class Server implements InCS, InCPP, InC {
	interface ToMyClients {
	@id(0)
	class FirstPack {}
	}
	
	interface HiddenVIP {}
}

class Client implements InKT, InTS, InRUST {
	interface ToServer {}
}
class ClientServerLink extends AdvProtocol implements Client.ToServer, Server.ToMyClients {}















































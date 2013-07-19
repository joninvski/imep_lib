#include <map>
#include <list>
#include <cstddef>

#define DEF_BEACON_SKIPS  3

class IMEP
{

protected:
  typedef unsigned int NodeAddress;
  typedef std::map<NodeAddress, unsigned> connection_lst_t;
  connection_lst_t conn_lst_;
  unsigned int beacon_skips_;
  void (*lost_conn_callback_)(void* none, int a, int b);
  void (*send_beacon_msg_callback_)(void* none);

public:
  /* Default constructor */
  IMEP(void (*send_beacon_callback)(void*));
  IMEP(int beacon_skips, void (*send_beacon_callback)(void*));

  ~IMEP();

  /**
   * @brief Sets the callback to be called when a connection is lost
   *
   * If null is passed, no callback will be called
   *
   * @param callback
   */
  void setConnectionLostCallback(void (*callback)(void*, int, int) );

  /**
   * @brief Set the callback for Imep to call when it wants to sends a message
   *
   * @param function to call
   */
  void setSendBeaconMsgCallback(void (*callback)(void*));

  /**
   * @brief Indicates that a time unit has passed
   *
   * 1. Sends beacons
   *
   * 2. For each connection which has not been updated during beacon_skips
   * remove it from the connection list and call the supplied callback
   */
  void pass_time();

  /**
   * @brief Gets the present active connection list as a std::list
   *
   * @return A std::list of nodeAddresses of active connections
   */
  std::list<NodeAddress> getActiveConnections();

  /**
   * @brief Tells IMEP that a beacon message has been received
   *
   * @param nodeAddress of the node who sent the beacon
   */
  void receiveBeaconMessage(NodeAddress nodeAddress);

};

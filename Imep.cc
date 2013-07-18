#include <map>
#include <list>

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
  IMEP(void (*send_beacon_callback)(void*))
    {
      beacon_skips_ = DEF_BEACON_SKIPS;
      send_beacon_msg_callback_ = send_beacon_callback;
      lost_conn_callback_ = NULL;
    }

  IMEP(int beacon_skips, void (*send_beacon_callback)(void*))
    {
      beacon_skips_ = beacon_skips;
      send_beacon_msg_callback_ = send_beacon_callback;
      lost_conn_callback_ = NULL;
    }

  ~IMEP()
    {
      return;
    }

  /**
   * @brief Sets the callback to be called when a connection is lost
   *
   * If null is passed, no callback will be called
   *
   * @param callback
   */
  void setConnectionLostCallback(void (*callback)(void*, int, int) )
    {
      lost_conn_callback_ = callback;
    }

  /**
   * @brief Set the callback for Imep to call when it wants to sends a message
   *
   * @param function to call
   */
  void setSendBeaconMsgCallback(void (*callback)(void*))
    {
      send_beacon_msg_callback_ = callback;
    }

  /**
   * @brief Indicates that a time unit has passed
   *
   * 1. Sends beacons
   *
   * 2. For each connection which has not been updated during beacon_skips
   * remove it from the connection list and call the supplied callback
   */
  void pass_time()
    {
      /* 1st part - Send the beacons */
      send_beacon_msg_callback_((void*) "hello");

      /* 2nd Part - Check if it was not updated */
      for(connection_lst_t::iterator it = conn_lst_.begin(); it != conn_lst_.end(); ++it) {
          it->second--;

          if(it->second <= 0)
            {
              /* I dont remove it from a list as a entry with value 0 is considered as removed */

              /* Do the callback informing the connection is down */
              if(send_beacon_msg_callback_) lost_conn_callback_((void *) "ola", 1, 2);
            }

          else
            {
              (it->second)--;
            }
      }
    }

  /**
   * @brief Gets the present active connection list as a std::list
   *
   * @return A std::list of nodeAddresses of active connections
   */
  std::list<NodeAddress> getActiveConnections()
    {
      std::list<NodeAddress> l = std::list<NodeAddress>();

      for(connection_lst_t::iterator it = conn_lst_.begin(); it != conn_lst_.end(); ++it)
        {
          if(it->second > 0)
            {
              l.push_back(it->first);
            }
        }

      return l;
    }

  /**
   * @brief Tells IMEP that a beacon message has been received
   *
   * @param nodeAddress of the node who sent the beacon
   */
  void receiveBeaconMessage(NodeAddress nodeAddress)
    {
      conn_lst_[nodeAddress] = beacon_skips_;
    }

};

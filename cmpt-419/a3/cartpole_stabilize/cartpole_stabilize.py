import tensorflow as tf
import tensorflow.contrib.slim as slim
import numpy as np
import gym
import matplotlib.pyplot as plt

def compute_advantage(j, r, gamma):
    ### Part f) Advantage computation
    """ Computes the advantage function from data
        Inputs:
            j     -- list of time steps 
                    (eg. j == [0, 1, 2, 3, 0, 1, 2, 3, 4, 5] means that there 
                     are two episodes, one with four time steps and another with
                     6 time steps)
            r     -- list of rewards from episodes corresponding to time steps j
            gamma -- discount factor
        
        Output:
            advantage -- vector of advantages correponding to time steps j
    """
    
    return advantage

class agent():
    def __init__(self, lr, s_size, a_size, h1_size, h2_size):
        """ Initialize the RL agent 
        Inputs:
            lr      -- learning rate
            s_size  -- # of states
            a_size  -- # of actions (output of policy network)
            h1_size -- # of neurons in first hidden layer of policy network
            h2_size -- # of neurons in second hidden layer of policy network
        """
        
        # Data consists of a list of states, actions, and rewards
        self.advantage_data = tf.placeholder(shape=[None], dtype=tf.float32)
        self.action_data = tf.placeholder(shape=[None], dtype=tf.int32)        
        self.state_data = tf.placeholder(shape=[None,s_size], dtype=tf.float32)
        
        ### --- Part c) Define the policy network ---
        # Input should be the state (defined above)
        # Output should be the probability distribution of actions

        ### -----------------------------------------
        
        ### -- Part d) Compute probabilities of realized actions (from data) --
        # Indices of policy network outputs (which are probabilities) 
        # corresponding to action data
        
        ### -------------------------------------------------------------------
        
        ### -- Part e) Define loss function for policy improvement procedure --
        
        ### -------------------------------------------------------------------
        
        # Gradient computation
        tvars = tf.trainable_variables()
        self.gradients = tf.gradients(self.loss, tvars)
        
        # Apply update step
        optimizer = tf.train.AdamOptimizer(learning_rate=lr)
        self.update_batch = optimizer.apply_gradients(zip(self.gradients, tvars))
    # --- end def ---
# --- end class ---

##### Main script #####
env = gym.make('CartPole-v2') # Initialize gym environment
gamma = 0.99                  # Discount factor

# initialize tensor flow model
tf.reset_default_graph()

### --- Part g) create the RL agent ---
# myAgent = agent(...)  
# uncomment fill in arguments of the above line to initialize an RL agent whose
# policy network contains two hidden layers with 8 neurons each

### -----------------------------------

total_episodes = 2500 # maximum # of training episodes
max_steps = 500 # maximum # of steps per episode (overridden in gym environment)
update_frequency = 5 # number of episodes between policy network updates

# Begin tensorflow session
init = tf.global_variables_initializer()   
with tf.Session() as sess:
    # Initialization
    sess.run(init)
    i = 0
    
    ep_rewards = []
    history = []
    
    while i < total_episodes:
        # reset environment
        s = env.reset() 

        for j in range(max_steps):
            # Visualize behaviour every 100 episodes
            if i % 100 == 0:
                env.render()
            # --- end if ---
            
            ### ------------ Part g) -------------------
            ### Probabilistically pick an action given policy network outputs.
            
            ### ----------------------------------------
            
            # Get reward for taking an action, and store data from the episode
            s1,r,d,_ = env.step(a) #
            history.append([j,s,a,r,s1])
            s = s1

            if d == True: # Update the network when episode is done
                # Update network every "update_frequency" episodes
                if i % update_frequency == 0 and i != 0:
                    # Compute advantage
                    history = np.array(history)
                    advantage = compute_advantage(history[:,0], history[:,3], \
                                                  gamma)
                    
                    ### --- Part g) Perform policy update ---
                    
                    ### -------------------------------------
                    
                    # Reset history
                    history = []
                # --- end if ---

                break
            # --- end if ---
        # --- end for ---

        i += 1
    # --- end while ---
    
# --- end of script ---
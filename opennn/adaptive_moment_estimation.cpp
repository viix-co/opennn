//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   A D A P T I V E   M O M E N T   E S T I M A T I O N
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "adaptive_moment_estimation.h"

namespace OpenNN
{

/// Default constructor.
/// It creates a adaptive moment estimation optimization algorithm not associated to any loss index object.
/// It also initializes the class members to their default values.

AdaptiveMomentEstimation::AdaptiveMomentEstimation()
:OptimizationAlgorithm()
{
   set_default();
}


/// Loss index constructor.
/// It creates a adaptive moment estimation optimization algorithm associated to a loss index.
/// It also initializes the class members to their default values.
/// @param new_loss_index_pointer Pointer to a loss index object.

AdaptiveMomentEstimation::AdaptiveMomentEstimation(LossIndex* new_loss_index_pointer)
: OptimizationAlgorithm(new_loss_index_pointer)
{
   set_default();
}




/// XML constructor.
/// It creates a gradient descent optimization algorithm not associated to any loss index object.
/// It also loads the class members from a XML document.
/// @param document TinyXML document with the members of a gradient descent object.

AdaptiveMomentEstimation::AdaptiveMomentEstimation(const tinyxml2::XMLDocument& document)
: OptimizationAlgorithm(document)
{
   set_default();

   from_XML(document);
}


/// Destructor.

AdaptiveMomentEstimation::~AdaptiveMomentEstimation()
{
}


/// Returns the initial learning rate.

const type& AdaptiveMomentEstimation::get_initial_learning_rate() const
{
   return initial_learning_rate;
}


/// Returns beta 1.

const type& AdaptiveMomentEstimation::get_beta_1() const
{
   return beta_1;
}


/// Returns beta 2.

const type& AdaptiveMomentEstimation::get_beta_2() const
{
   return beta_2;
}


/// Returns epsilon.

const type& AdaptiveMomentEstimation::get_epsilon() const
{
   return epsilon;
}


/// Returns the minimum value for the norm of the parameters vector at wich a warning message is
/// written to the screen.

const type& AdaptiveMomentEstimation::get_warning_parameters_norm() const
{
   return warning_parameters_norm;
}


/// Returns the minimum value for the norm of the gradient vector at wich a warning message is written
/// to the screen.

const type& AdaptiveMomentEstimation::get_warning_gradient_norm() const
{
   return warning_gradient_norm;
}


/// Returns the value for the norm of the parameters vector at wich an error message is
/// written to the screen and the program exits.

const type& AdaptiveMomentEstimation::get_error_parameters_norm() const
{
   return error_parameters_norm;
}


/// Returns the value for the norm of the gradient vector at wich an error message is written
/// to the screen and the program exits.

const type& AdaptiveMomentEstimation::get_error_gradient_norm() const
{
   return error_gradient_norm;
}


/// Returns the minimum norm of the parameter increment vector used as a stopping criteria when training.

const type& AdaptiveMomentEstimation::get_minimum_parameters_increment_norm() const
{
   return minimum_parameters_increment_norm;
}


/// Returns the minimum loss improvement during training.

const type& AdaptiveMomentEstimation::get_minimum_loss_increase() const
{
   return minimum_loss_decrease;
}


/// Returns the goal value for the loss.
/// This is used as a stopping criterion when training a neural network

const type& AdaptiveMomentEstimation::get_loss_goal() const
{
   return loss_goal;
}


/// Returns the goal value for the norm of the error function gradient.
/// This is used as a stopping criterion when training a neural network

const type& AdaptiveMomentEstimation::get_gradient_norm_goal() const
{
   return gradient_norm_goal;
}


/// Returns the maximum number of selection error increases during the training process.

const Index& AdaptiveMomentEstimation::get_maximum_selection_error_increases() const
{
   return maximum_selection_error_increases;
}


/// Returns the maximum training time.

const type& AdaptiveMomentEstimation::get_maximum_time() const
{
   return maximum_time;
}


/// Returns true if the final model will be the neural network with the minimum selection error, false otherwise.

const bool& AdaptiveMomentEstimation::get_return_minimum_selection_error_neural_network() const
{
    return return_minimum_selection_error_neural_network;
}


/// Returns true if the selection error decrease stopping criteria has to be taken in account, false otherwise.

const bool& AdaptiveMomentEstimation::get_apply_early_stopping() const
{
    return apply_early_stopping;
}


/// Returns true if the error history vector is to be reserved, and false otherwise.

const bool& AdaptiveMomentEstimation::get_reserve_training_error_history() const
{
   return reserve_training_error_history;
}


/// Returns true if the selection error history vector is to be reserved, and false otherwise.

const bool& AdaptiveMomentEstimation::get_reserve_selection_error_history() const
{
   return reserve_selection_error_history;
}


/// Sets a pointer to a loss index object to be associated to the gradient descent object.
/// It also sets that loss index to the learning rate algorithm.
/// @param new_loss_index_pointer Pointer to a loss index object.

void AdaptiveMomentEstimation::set_loss_index_pointer(LossIndex* new_loss_index_pointer)
{
   loss_index_pointer = new_loss_index_pointer;
}


void AdaptiveMomentEstimation::set_default()
{
   // TRAINING OPERATORS

   initial_learning_rate = static_cast<type>(0.001);
   initial_decay = static_cast<type>(0.0);
   beta_1 = static_cast<type>(0.9);
   beta_2 = static_cast<type>(0.999);

   epsilon =static_cast<type>(1.e-7);

   // TRAINING PARAMETERS

   warning_parameters_norm = 1.0e6;
   warning_gradient_norm = 1.0e6;
   error_parameters_norm = 1.0e9;
   error_gradient_norm = 1.0e9;

   // Stopping criteria

   minimum_parameters_increment_norm = static_cast<type>(0.0);
   minimum_loss_decrease = static_cast<type>(0.0);
   loss_goal = -numeric_limits<type>::max();
   gradient_norm_goal = static_cast<type>(0.0);
   maximum_selection_error_increases = 1000000;
   maximum_time = 1000.0;
   maximum_epochs_number = 10000;
   return_minimum_selection_error_neural_network = false;
   apply_early_stopping = true;

   // TRAINING HISTORY

   reserve_training_error_history = true;
   reserve_selection_error_history = false;

   // UTILITIES

   display = true;
   display_period = 1;
}


/// Makes the training history of all variables to reseved or not in memory:
/// <ul>
/// <li> Parameters.
/// <li> Parameters norm.
/// <li> Loss.
/// <li> Gradient.
/// <li> Gradient norm.
/// <li> Selection loss.
/// <li> Training direction.
/// <li> Training direction norm.
/// <li> Training rate.
/// </ul>
/// @param new_reserve_all_training_history True if the training history of all variables is to be reserved, false otherwise.

void AdaptiveMomentEstimation::set_reserve_all_training_history(const bool& new_reserve_all_training_history)
{
   reserve_training_error_history = new_reserve_all_training_history;

   reserve_selection_error_history = new_reserve_all_training_history;
}


/// Sets a new learning rate.
/// @param new_learning_rate.

void AdaptiveMomentEstimation::set_initial_learning_rate(const type& new_learning_rate)
{
    initial_learning_rate= new_learning_rate;
}


/// Sets beta 1 generally close to 1.
/// @param new_beta_1.

void AdaptiveMomentEstimation::set_beta_1(const type& new_beta_1)
{
    beta_1= new_beta_1;
}


/// Sets beta 2 generally close to 1.
/// @param new_beta_2.

void AdaptiveMomentEstimation::set_beta_2(const type& new_beta_2)
{
    beta_2= new_beta_2;
}


/// Sets epsilon.
/// @param epsilon.

void AdaptiveMomentEstimation::set_epsilon(const type& new_epsilon)
{
    epsilon= new_epsilon;
}


/// Sets a new value for the parameters vector norm at which a warning message is written to the screen.
/// @param new_warning_parameters_norm Warning norm of parameters vector value.

void AdaptiveMomentEstimation::set_warning_parameters_norm(const type& new_warning_parameters_norm)
{
   #ifdef __OPENNN_DEBUG__

   if(new_warning_parameters_norm < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_warning_parameters_norm(const type&) method.\n"
             << "Warning parameters norm must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set warning parameters norm

   warning_parameters_norm = new_warning_parameters_norm;
}


/// Sets a new value for the gradient vector norm at which
/// a warning message is written to the screen.
/// @param new_warning_gradient_norm Warning norm of gradient vector value.

void AdaptiveMomentEstimation::set_warning_gradient_norm(const type& new_warning_gradient_norm)
{
   
   #ifdef __OPENNN_DEBUG__

   if(new_warning_gradient_norm < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_warning_gradient_norm(const type&) method.\n"
             << "Warning gradient norm must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set warning gradient norm

   warning_gradient_norm = new_warning_gradient_norm;
}


/// Sets a new value for the parameters vector norm at which an error message is written to the
/// screen and the program exits.
/// @param new_error_parameters_norm Error norm of parameters vector value.

void AdaptiveMomentEstimation::set_error_parameters_norm(const type& new_error_parameters_norm)
{
   

   #ifdef __OPENNN_DEBUG__

   if(new_error_parameters_norm < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_error_parameters_norm(const type&) method.\n"
             << "Error parameters norm must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set error parameters norm

   error_parameters_norm = new_error_parameters_norm;
}


/// Sets a new value for the gradient vector norm at which an error message is written to the screen
/// and the program exits.
/// @param new_error_gradient_norm Error norm of gradient vector value.

void AdaptiveMomentEstimation::set_error_gradient_norm(const type& new_error_gradient_norm)
{
   #ifdef __OPENNN_DEBUG__

   if(new_error_gradient_norm < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_error_gradient_norm(const type&) method.\n"
             << "Error gradient norm must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set error gradient norm

   error_gradient_norm = new_error_gradient_norm;
}


/// Set the a new maximum for the epochs number.
/// @param new_maximum_epochs number New maximum epochs number.

void AdaptiveMomentEstimation:: set_maximum_epochs_number(const Index& new_maximum_epochs_number)
{
   #ifdef __OPENNN_DEBUG__

   if(new_maximum_epochs_number < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_maximum_epochs_number(const type&) method.\n"
             << "Maximum epochs number must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set maximum_epochs number

   maximum_epochs_number = new_maximum_epochs_number;
}


/// Sets a new value for the minimum parameters increment norm stopping criterion.
/// @param new_minimum_parameters_increment_norm Value of norm of parameters increment norm used to stop training.

void AdaptiveMomentEstimation::set_minimum_parameters_increment_norm(const type& new_minimum_parameters_increment_norm)
{
   #ifdef __OPENNN_DEBUG__

   if(new_minimum_parameters_increment_norm < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void new_minimum_parameters_increment_norm(const type&) method.\n"
             << "Minimum parameters increment norm must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set error training rate

   minimum_parameters_increment_norm = new_minimum_parameters_increment_norm;
}


/// Sets a new minimum loss improvement during training.
/// @param new_minimum_loss_increase Minimum improvement in the loss between two iterations.

void AdaptiveMomentEstimation::set_minimum_loss_increase(const type& new_minimum_loss_increase)
{
   #ifdef __OPENNN_DEBUG__

   if(new_minimum_loss_increase < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_minimum_loss_increase(const type&) method.\n"
             << "Minimum loss improvement must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set minimum loss improvement

   minimum_loss_decrease = new_minimum_loss_increase;
}


/// Sets a new goal value for the loss.
/// This is used as a stopping criterion when training a neural network
/// @param new_loss_goal Goal value for the loss.

void AdaptiveMomentEstimation::set_loss_goal(const type& new_loss_goal)
{
   loss_goal = new_loss_goal;
}


/// Sets a new the goal value for the norm of the error function gradient.
/// This is used as a stopping criterion when training a neural network
/// @param new_gradient_norm_goal Goal value for the norm of the error function gradient.

void AdaptiveMomentEstimation::set_gradient_norm_goal(const type& new_gradient_norm_goal)
{
   #ifdef __OPENNN_DEBUG__

   if(new_gradient_norm_goal < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_gradient_norm_goal(const type&) method.\n"
             << "Gradient norm goal must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set gradient norm goal

   gradient_norm_goal = new_gradient_norm_goal;
}


/// Sets a new maximum number of selection error increases.
/// @param new_maximum_selection_error_increases Maximum number of iterations in which the selection evalutation decreases.

void AdaptiveMomentEstimation::set_maximum_selection_error_increases(const Index& new_maximum_selection_error_increases)
{
   maximum_selection_error_increases = new_maximum_selection_error_increases;
}


/// Sets a new maximum training time.
/// @param new_maximum_time Maximum training time.

void AdaptiveMomentEstimation::set_maximum_time(const type& new_maximum_time)
{
   #ifdef __OPENNN_DEBUG__

   if(new_maximum_time < static_cast<type>(0.0))
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_maximum_time(const type&) method.\n"
             << "Maximum time must be equal or greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   // Set maximum time

   maximum_time = new_maximum_time;
}


/// Makes the minimum selection error neural network of all the iterations to be returned or not.
/// @param new_return_minimum_selection_error_neural_network True if the final model will be the neural network with the minimum selection error, false otherwise.

void AdaptiveMomentEstimation::set_return_minimum_selection_error_neural_network(const bool& new_return_minimum_selection_error_neural_network)
{
   return_minimum_selection_error_neural_network = new_return_minimum_selection_error_neural_network;
}


/// Makes the selection error decrease stopping criteria has to be taken in account or not.
/// @param new_apply_early_stopping True if the selection error decrease stopping criteria has to be taken in account, false otherwise.

void AdaptiveMomentEstimation::set_apply_early_stopping(const bool& new_apply_early_stopping)
{
    apply_early_stopping = new_apply_early_stopping;
}


/// Makes the error history vector to be reseved or not in memory.
/// @param new_reserve_training_error_history True if the error history vector is to be reserved, false otherwise.

void AdaptiveMomentEstimation::set_reserve_training_error_history(const bool& new_reserve_training_error_history)
{
   reserve_training_error_history = new_reserve_training_error_history;
}


/// Makes the selection error history to be reserved or not in memory.
/// This is a vector.
/// @param new_reserve_selection_error_history True if the selection error history is to be reserved, false otherwise.

void AdaptiveMomentEstimation::set_reserve_selection_error_history(const bool& new_reserve_selection_error_history)
{
   reserve_selection_error_history = new_reserve_selection_error_history;
}


/// Sets a new number of iterations between the training showing progress.
/// @param new_display_period
/// Number of iterations between the training showing progress.

void AdaptiveMomentEstimation::set_display_period(const Index& new_display_period)
{
   
   #ifdef __OPENNN_DEBUG__

   if(new_display_period <= 0)
   {
      ostringstream buffer;

      buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
             << "void set_display_period(const type&) method.\n"
             << "First training rate must be greater than 0.\n";

      throw logic_error(buffer.str());
   }

   #endif

   display_period = new_display_period;
}


/// Trains a neural network with an associated loss index,
/// according to the gradient descent method.
/// Training occurs according to the training parameters and stopping criteria.
/// It returns a results structure with the history and the final values of the reserved variables.

OptimizationAlgorithm::Results AdaptiveMomentEstimation::perform_training()
{
   Results results;

   check();

   // Start training

   if(display) cout << "Training with adaptive moment estimator \"Adam\" ...\n";

   // Data set stuff

   DataSet* data_set_pointer = loss_index_pointer->get_data_set_pointer();

//   const Tensor<type, 2>& data = data_set_pointer->get_data();

   const Index selection_instances_number = data_set_pointer->get_selection_instances_number();

   const Index batch_instances_number = data_set_pointer->get_batch_instances_number();

//   const Tensor<Index, 1>& input_variables_dimensions = data_set_pointer->get_input_variables_dimensions();
//   const Tensor<Index, 1>& target_variables_dimensions = data_set_pointer->get_input_variables_dimensions();

   const Tensor<Index, 1> input_variables_indices = data_set_pointer->get_input_variables_indices();
   const Tensor<Index, 1> target_variables_indices = data_set_pointer->get_target_variables_indices();

   DataSet::Batch batch(data_set_pointer);

   // Neural network stuff

   NeuralNetwork* neural_network_pointer = loss_index_pointer->get_neural_network_pointer();

   const Index parameters_number = neural_network_pointer->get_parameters_number();

   Tensor<type, 1> parameters = neural_network_pointer->get_parameters();
   Tensor<type, 1> parameters_increment(parameters_number);

   type parameters_norm = static_cast<type>(0.0);

   NeuralNetwork::ForwardPropagation forward_propagation(batch_instances_number, neural_network_pointer);

   // Loss index stuff

   LossIndex::BackPropagation first_order_loss(loss_index_pointer);

   type training_error = static_cast<type>(0.0);

   type selection_error = static_cast<type>(0.0);
   type old_selection_error = static_cast<type>(0.0);

   type loss = static_cast<type>(0.0);
   type gradient_norm = static_cast<type>(0.0);

   // Optimization algorithm stuff

   type learning_rate = static_cast<type>(0.0);

   Index selection_error_increases = 0;

   Tensor<type, 1> minimum_selection_error_parameters(parameters_number);
   type minimum_selection_error = numeric_limits<type>::max();

   bool stop_training = false;

   time_t beginning_time, current_time;
   time(&beginning_time);
   type elapsed_time = static_cast<type>(0.0);

   results.resize_training_history(maximum_epochs_number + 1);

   Tensor<type, 1> gradient_exponential_decay(parameters_number);
   Tensor<type, 1> square_gradient_exponential_decay(parameters_number);

   Tensor<type, 1> last_gradient_exponential_decay(parameters_number);
   Tensor<type, 1> last_square_gradient_exponential_decay(parameters_number);

   Index iteration_count = 0;

    bool is_forecasting = false;

    if(neural_network_pointer->has_long_short_term_memory_layer() || neural_network_pointer->has_recurrent_layer()) is_forecasting = true;

   // Main loop

   for(Index epoch = 0; epoch <= maximum_epochs_number; epoch++)
   {
       const Tensor<Index, 2> training_batches = data_set_pointer->get_training_batches(!is_forecasting);

       const Index batches_number = training_batches.dimension(0);

       parameters_norm = l2_norm(parameters);

       if(display && parameters_norm >= warning_parameters_norm) cout << "OpenNN Warning: Parameters norm is " << parameters_norm << ".\n";

       loss = static_cast<type>(0.0);

       for(Index iteration = 0; iteration < batches_number; iteration++)
       {
           iteration_count++;

           // Data set

           data_set_pointer->get_subtensor_data(training_batches.chip(iteration,0), input_variables_indices);
           data_set_pointer->get_subtensor_data(training_batches.chip(iteration,0), target_variables_indices);
//           data.get_tensor(training_batches[iteration], input_variables_indices, input_variables_dimensions, batch.inputs_2d);
//           data.get_tensor(training_batches[iteration], target_variables_indices, target_variables_dimensions, batch.targets_2d);

           // Neural network
/*@todo device*/
//           neural_network_pointer->calculate_forward_propagation(batch, forward_propagation);

           // Loss index
/*@todo device*/
//           loss_index_pointer->calculate_first_order_loss(batch, forward_propagation, first_order_loss);

           learning_rate = initial_learning_rate*sqrt(static_cast<type>(1.0) - pow(beta_2, static_cast<type>(iteration_count)))/(static_cast<type>(1.0) - pow(beta_1, static_cast<type>(iteration_count)));

           // Loss

           loss += first_order_loss.loss;

           // Gradient

           gradient_exponential_decay = last_gradient_exponential_decay*beta_1 + first_order_loss.gradient*(1 - beta_1);

           last_gradient_exponential_decay = gradient_exponential_decay;

           square_gradient_exponential_decay = last_square_gradient_exponential_decay*beta_2 + first_order_loss.gradient*first_order_loss.gradient*(1 - beta_2);

           last_square_gradient_exponential_decay = square_gradient_exponential_decay;

           // Update parameters

           parameters -= gradient_exponential_decay*learning_rate/(square_gradient_exponential_decay.sqrt() + epsilon);

           neural_network_pointer->set_parameters(parameters);
        }

       // Gradient

       gradient_norm = l2_norm(first_order_loss.gradient);

        // Loss

       training_error = loss/static_cast<type>(batches_number);

       if(selection_instances_number > 0) selection_error = loss_index_pointer->calculate_selection_error();

       if(epoch == 0)
       {
          minimum_selection_error = selection_error;
          minimum_selection_error_parameters = parameters;
       }
       else if(epoch != 0 && selection_error > old_selection_error)
       {
          selection_error_increases++;
       }
       else if(selection_error <= minimum_selection_error)
       {
          minimum_selection_error = selection_error;
          minimum_selection_error_parameters = parameters;
       }

       // Elapsed time

       time(&current_time);
       elapsed_time = static_cast<type>(difftime(current_time, beginning_time));

       // Training history loss index

       if(reserve_training_error_history) results.training_error_history[epoch] = training_error;

       if(reserve_selection_error_history) results.selection_error_history[epoch] = selection_error;

       // Stopping Criteria

        if(selection_error_increases >= maximum_selection_error_increases && apply_early_stopping)
        {
           if(display)
           {
              cout << "Epoch " << epoch << ", iteration " << epoch << ": Maximum selection error increases reached.\n"
                   << "Selection error increases: " << selection_error_increases << endl;
           }

           stop_training = true;

           results.stopping_condition = MaximumSelectionErrorIncreases;
        }

        else if(epoch == maximum_epochs_number)
        {
           if(display)
           {
              cout << "Epoch " << epoch << ": Maximum number of epochs reached.\n";
           }

           stop_training = true;

           results.stopping_condition = MaximumEpochsNumber;
        }

        else if(elapsed_time >= maximum_time)
        {
           if(display)
           {
              cout << "Epoch " << epoch << ": Maximum training time reached.\n";
           }

           stop_training = true;

           results.stopping_condition = MaximumTime;
        }

        else if(training_error <= loss_goal)
        {
           if(display)
           {
              cout << "Epoch " << epoch << ": Loss goal reached.\n";
           }

           stop_training = true;

           results.stopping_condition  = LossGoal;
        }

        if(epoch != 0 && epoch % save_period == 0)
        {
              neural_network_pointer->save(neural_network_file_name);
        }

        if(stop_training)
        {
           if(display)
           {                              
              cout << "Parameters norm: " << parameters_norm << "\n"
                   << "Training loss: " << training_error << "\n"
                   << "Gradient norm: " << gradient_norm << "\n"
                   << loss_index_pointer->write_information()
                   << "Learning rate: " << learning_rate << "\n"
//                   << "Elapsed time: " << write_elapsed_time(elapsed_time)<<"\n"
                   << "Selection error: " << selection_error << endl;
           }

           results.resize_training_history(1+epoch);

           results.final_parameters = parameters;

           results.final_parameters_norm = parameters_norm;

           results.final_training_error = training_error;

           results.final_selection_error = selection_error;

           results.final_gradient_norm = gradient_norm;

           results.elapsed_time = elapsed_time;

           results.epochs_number = epoch;

           break;
        }
        else if(display && epoch % display_period == 0)
        {
           cout << "Epoch " << epoch << ";\n"
                << "Training loss: " << training_error << "\n";
//                << "Batch size: " << batch_instances_number << "\n"
//                << "Gradient norm: " << gradient_norm << "\n"
//                << loss_index_pointer->write_information()
//                << "Learning rate: " << learning_rate<< "\n"
//                << "Elapsed time: " << write_elapsed_time(elapsed_time)<<"\n";
//                << "Selection error: " << selection_error << endl;

        }

          // Update stuff

          old_selection_error = selection_error;

       if(stop_training) break;
   }

   if(return_minimum_selection_error_neural_network)
   {
       parameters = minimum_selection_error_parameters;
       parameters_norm = l2_norm(parameters);

       neural_network_pointer->set_parameters(parameters);

       selection_error = minimum_selection_error;
   }

   results.final_parameters = parameters;
   results.final_parameters_norm = parameters_norm;
   results.final_training_error = training_error;
   results.final_selection_error = selection_error;
   results.final_gradient_norm = gradient_norm;
   results.elapsed_time = elapsed_time;

   return results;
}


/// @todo Gives error

void AdaptiveMomentEstimation::perform_training_void()
{
 //   perform_training();
}


string AdaptiveMomentEstimation::write_optimization_algorithm_type() const
{
   return "GRADIENT_DESCENT";
}


/// Writes as matrix of strings the most representative atributes.

Tensor<string, 2> AdaptiveMomentEstimation::to_string_matrix() const
{
/*
    ostringstream buffer;

    Tensor<string, 1> labels;
    Tensor<string, 1> values;

   // Minimum parameters increment norm

   labels.push_back("Minimum parameters increment norm");

   buffer.str("");
   buffer << minimum_parameters_increment_norm;

   values.push_back(buffer.str());

   // Minimum loss decrease

   labels.push_back("Minimum loss decrease");

   buffer.str("");
   buffer << minimum_loss_decrease;

   values.push_back(buffer.str());

   // Loss goal

   labels.push_back(" Loss goal");

   buffer.str("");
   buffer << loss_goal;

   values.push_back(buffer.str());

   // Gradient norm goal

   labels.push_back("Gradient norm goal");

   buffer.str("");
   buffer << gradient_norm_goal;

   values.push_back(buffer.str());

   // Maximum selection error decreases

   labels.push_back("Maximum selection error increases");

   buffer.str("");
   buffer << maximum_selection_error_increases;

   values.push_back(buffer.str());

   // Maximum iterations number

   labels.push_back("Maximum epoch number");

   buffer.str("");
   buffer << maximum_epochs_number;

   values.push_back(buffer.str());

   // Maximum time

   labels.push_back("Maximum time");

   buffer.str("");
   buffer << maximum_time;

   values.push_back(buffer.str());

   // Reserve training error history

   labels.push_back("Reserve loss history");

   buffer.str("");

   if(reserve_training_error_history)
   {
       buffer << "true";
   }
   else
   {
       buffer << "false";
   }

   values.push_back(buffer.str());

   // Reserve selection error history

   labels.push_back("Reserve selection error history");

   buffer.str("");

   if(reserve_selection_error_history)
   {
       buffer << "true";
   }
   else
   {
       buffer << "false";
   }

   values.push_back(buffer.str());

   const Index rows_number = labels.dimension(0);
   const Index columns_number = 2;

   Tensor<string, 2> string_matrix(rows_number, columns_number);

   string_matrix.set_column(0, labels, "name");
   string_matrix.set_column(1, values, "value");

    return string_matrix;
*/
    return Tensor<string, 2>();
}


/// Serializes the training parameters, the stopping criteria and other user stuff
/// concerning the gradient descent object.

tinyxml2::XMLDocument* AdaptiveMomentEstimation::to_XML() const
{
   ostringstream buffer;

   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   // Optimization algorithm

   tinyxml2::XMLElement* root_element = document->NewElement("AdaptiveMomentEstimation");

   document->InsertFirstChild(root_element);

   tinyxml2::XMLElement* element = nullptr;
   tinyxml2::XMLText* text = nullptr;

   // Return minimum selection error neural network

   element = document->NewElement("ReturnMinimumSelectionErrorNN");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << return_minimum_selection_error_neural_network;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Apply early stopping

   element = document->NewElement("ApplyEarlyStopping");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << apply_early_stopping;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Warning parameters norm

   element = document->NewElement("WarningParametersNorm");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << warning_parameters_norm;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Warning gradient norm

   element = document->NewElement("WarningGradientNorm");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << warning_gradient_norm;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Error parameters norm

   element = document->NewElement("ErrorParametersNorm");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << error_parameters_norm;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Error gradient norm

   element = document->NewElement("ErrorGradientNorm");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << error_gradient_norm;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Minimum parameters increment norm

   element = document->NewElement("MinimumParametersIncrementNorm");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << minimum_parameters_increment_norm;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Minimum loss decrease

   element = document->NewElement("MinimumLossDecrease");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << minimum_loss_decrease;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Loss goal

   element = document->NewElement("LossGoal");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << loss_goal;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Gradient norm goal

   element = document->NewElement("GradientNormGoal");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << gradient_norm_goal;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Maximum selection error decreases

   element = document->NewElement("MaximumSelectionErrorIncreases");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << maximum_selection_error_increases;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Maximum iterations number

   element = document->NewElement("MaximumEpochsNumber");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << maximum_epochs_number;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Maximum time

   element = document->NewElement("MaximumTime");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << maximum_time;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Reserve training error history

   element = document->NewElement("ReserveTrainingErrorHistory");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << reserve_training_error_history;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Reserve selection error history

   element = document->NewElement("ReserveSelectionErrorHistory");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << reserve_selection_error_history;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

    //Reserve selection error history

   element = document->NewElement("ReserveSelectionErrorHistory");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << reserve_selection_error_history;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Display period

   element = document->NewElement("DisplayPeriod");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << display_period;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Save period

   element = document->NewElement("SavePeriod");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << save_period;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   // Neural network file name

   element = document->NewElement("NeuralNetworkFileName");
   root_element->LinkEndChild(element);

   text = document->NewText(neural_network_file_name.c_str());
   element->LinkEndChild(text);

   // Display warnings

   element = document->NewElement("Display");
   root_element->LinkEndChild(element);

   buffer.str("");
   buffer << display;

   text = document->NewText(buffer.str().c_str());
   element->LinkEndChild(text);

   return document;
}


/// Serializes the gradient descent object into a XML document of the TinyXML library without keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document.

void AdaptiveMomentEstimation::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    ostringstream buffer;

    // Batch size

    file_stream.OpenElement("BatchSize");

    buffer.str("");
    buffer << loss_index_pointer->get_data_set_pointer()->get_batch_instances_number();

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Return minimum selection error neural network

    file_stream.OpenElement("ReturnMinimumSelectionErrorNN");

    buffer.str("");
    buffer << return_minimum_selection_error_neural_network;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Apply early stopping

    file_stream.OpenElement("ApplyEarlyStopping");

    buffer.str("");
    buffer << apply_early_stopping;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Minimum parameters increment norm

    file_stream.OpenElement("MinimumParametersIncrementNorm");

    buffer.str("");
    buffer << minimum_parameters_increment_norm;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Minimum loss decrease

    file_stream.OpenElement("MinimumLossDecrease");

    buffer.str("");
    buffer << minimum_loss_decrease;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Loss goal

    file_stream.OpenElement("LossGoal");

    buffer.str("");
    buffer << loss_goal;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Gradient norm goal

    file_stream.OpenElement("GradientNormGoal");

    buffer.str("");
    buffer << gradient_norm_goal;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum selection error increases

    file_stream.OpenElement("MaximumSelectionErrorIncreases");

    buffer.str("");
    buffer << maximum_selection_error_increases;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum iterations number

    file_stream.OpenElement("MaximumEpochsNumber");

    buffer.str("");
    buffer << maximum_epochs_number;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Maximum time

    file_stream.OpenElement("MaximumTime");

    buffer.str("");
    buffer << maximum_time;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Reserve training error history

    file_stream.OpenElement("ReserveTrainingErrorHistory");

    buffer.str("");
    buffer << reserve_training_error_history;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Reserve selection error history

    file_stream.OpenElement("ReserveSelectionErrorHistory");

    buffer.str("");
    buffer << reserve_selection_error_history;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();
}


void AdaptiveMomentEstimation::from_XML(const tinyxml2::XMLDocument& document)
{
    const tinyxml2::XMLElement* root_element = document.FirstChildElement("AdaptiveMomentEstimation");

    if(!root_element)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: AdaptiveMomentEstimation class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Adaptative moment estimation element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    // Batch size

    const tinyxml2::XMLElement* batch_size_element = root_element->FirstChildElement("BatchSize");

    if(batch_size_element)
    {
        string new_batch_size = batch_size_element->GetText();

        try
        {
           loss_index_pointer->get_data_set_pointer()->set_batch_instances_number(new_batch_size != "0");
        }
        catch(const logic_error& e)
        {
           cerr << e.what() << endl;
        }
    }

    // Return minimum selection error neural network

    const tinyxml2::XMLElement* return_minimum_selection_error_neural_network_element = root_element->FirstChildElement("ReturnMinimumSelectionErrorNN");

    if(return_minimum_selection_error_neural_network_element)
    {
        string new_return_minimum_selection_error_neural_network = return_minimum_selection_error_neural_network_element->GetText();

        try
        {
           set_return_minimum_selection_error_neural_network(new_return_minimum_selection_error_neural_network != "0");
        }
        catch(const logic_error& e)
        {
           cerr << e.what() << endl;
        }
    }

    // Apply early stopping

    const tinyxml2::XMLElement* apply_early_stopping_element = root_element->FirstChildElement("ApplyEarlyStopping");

    if(apply_early_stopping_element)
    {
        string new_apply_early_stopping = apply_early_stopping_element->GetText();

        try
        {
            set_apply_early_stopping(new_apply_early_stopping != "0");
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }

   // Minimum parameters increment norm
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("MinimumParametersIncrementNorm");

       if(element)
       {
          const type new_minimum_parameters_increment_norm = static_cast<type>(atof(element->GetText()));

          try
          {
             set_minimum_parameters_increment_norm(new_minimum_parameters_increment_norm);
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

   // Minimum loss decrease
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("MinimumLossDecrease");

       if(element)
       {
          const type new_minimum_loss_increase = static_cast<type>(atof(element->GetText()));

          try
          {
             set_minimum_loss_increase(new_minimum_loss_increase);
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

   // Loss goal
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("LossGoal");

       if(element)
       {
          const type new_loss_goal = static_cast<type>(atof(element->GetText()));

          try
          {
             set_loss_goal(new_loss_goal);
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

   // Gradient norm goal
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("GradientNormGoal");

       if(element)
       {
          const type new_gradient_norm_goal = static_cast<type>(atof(element->GetText()));

          try
          {
             set_gradient_norm_goal(new_gradient_norm_goal);
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

   // Maximum selection error increases
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("MaximumSelectionErrorIncreases");

       if(element)
       {
          const Index new_maximum_selection_error_increases = static_cast<Index>(atoi(element->GetText()));

          try
          {
             set_maximum_selection_error_increases(new_maximum_selection_error_increases);
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

   // Maximum eochs number
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("MaximumEpochsNumber");

       if(element)
       {
          const Index new_maximum_epochs_number = static_cast<Index>(atoi(element->GetText()));

          try
          {
             set_maximum_epochs_number(new_maximum_epochs_number);
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

   // Maximum time
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("MaximumTime");

       if(element)
       {
          const type new_maximum_time = static_cast<type>(atof(element->GetText()));

          try
          {
             set_maximum_time(new_maximum_time);
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

   // Reserve training error history
   {
       const tinyxml2::XMLElement* element = root_element->FirstChildElement("ReserveTrainingErrorHistory");

       if(element)
       {
          const string new_reserve_training_error_history = element->GetText();

          try
          {
             set_reserve_training_error_history(new_reserve_training_error_history != "0");
          }
          catch(const logic_error& e)
          {
             cerr << e.what() << endl;
          }
       }
   }

    // Reserve selection error history
    {
        const tinyxml2::XMLElement* element = root_element->FirstChildElement("ReserveSelectionErrorHistory");

        if(element)
        {
           const string new_reserve_selection_error_history = element->GetText();

           try
           {
              set_reserve_selection_error_history(new_reserve_selection_error_history != "0");
           }
           catch(const logic_error& e)
           {
              cerr << e.what() << endl;
           }
        }
    }
}

}

// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

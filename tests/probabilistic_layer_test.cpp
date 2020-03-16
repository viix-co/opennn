//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   P R O B A B I L I S T I C   L A Y E R   T E S T   C L A S S           
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "probabilistic_layer_test.h"


ProbabilisticLayerTest::ProbabilisticLayerTest() : UnitTesting()
{

}


ProbabilisticLayerTest::~ProbabilisticLayerTest()
{

}


void ProbabilisticLayerTest::test_constructor() //<---
{
   cout << "test_constructor\n";

   // Default constructor

   ProbabilisticLayer probabilistic_layer_l1;

//   assert_true(probabilistic_layer_l1.get_input_variables_dimensions()(0) == 0, LOG);
   assert_true(probabilistic_layer_l1.get_inputs_number() == 0, LOG);
   assert_true(probabilistic_layer_l1.get_neurons_number() == 0, LOG);
   assert_true(probabilistic_layer_l1.get_biases_number() == 0, LOG);
   assert_true(probabilistic_layer_l1.get_synaptic_weights_number() == 0, LOG);
   assert_true(probabilistic_layer_l1.get_parameters_number() == 0, LOG);


   // Probabilistic neurons number constructor

   ProbabilisticLayer probabilistic_layer_l2;

   probabilistic_layer_l2.set_neurons_number(3);

   assert_true(probabilistic_layer_l2.get_inputs_number() == 0, LOG);
   assert_true(probabilistic_layer_l2.get_neurons_number() == 3, LOG);
   assert_true(probabilistic_layer_l2.get_biases_number() == 3, LOG);
   assert_true(probabilistic_layer_l2.get_synaptic_weights_number() == 0, LOG);
   assert_true(probabilistic_layer_l2.get_parameters_number() == 3, LOG);

   // Copy constructor

   ProbabilisticLayer probabilistic_layer_l3(probabilistic_layer_l2);

   probabilistic_layer_l3.set_neurons_number(probabilistic_layer_l2.get_neurons_number());

   assert_true(probabilistic_layer_l3.get_inputs_number() == 0, LOG);
   assert_true(probabilistic_layer_l3.get_neurons_number() == 3, LOG);
   assert_true(probabilistic_layer_l3.get_biases_number() == 3, LOG);
   assert_true(probabilistic_layer_l3.get_synaptic_weights_number() == 0, LOG);
   assert_true(probabilistic_layer_l3.get_parameters_number() == 3, LOG);
}

void ProbabilisticLayerTest::test_destructor()
{
   cout << "test_destructor\n";
}

void ProbabilisticLayerTest::test_assignment_operator()
{
   cout << "test_assignment_operator\n";

   ProbabilisticLayer probabilistic_layer_l1;
   ProbabilisticLayer probabilistic_layer_l2;

   // Test

   probabilistic_layer_l1.set_neurons_number(2);
   probabilistic_layer_l2.set_neurons_number(probabilistic_layer_l1.get_neurons_number());

   assert_true(probabilistic_layer_l2.get_inputs_number() == 0, LOG);
   assert_true(probabilistic_layer_l2.get_neurons_number() == 2, LOG);
   assert_true(probabilistic_layer_l2.get_biases_number() == 2, LOG);
   assert_true(probabilistic_layer_l2.get_synaptic_weights_number() == 0, LOG);
   assert_true(probabilistic_layer_l2.get_parameters_number() == 2, LOG);
}

void ProbabilisticLayerTest::test_get_inputs_number()
{
   cout << "test_get_inputs_number\n";

   ProbabilisticLayer probabilistic_layer;

   // Test 0
   probabilistic_layer.set();
   assert_true(probabilistic_layer.get_inputs_number() == 0, LOG);

   // Test 1
   probabilistic_layer.set_inputs_number(1);
   assert_true(probabilistic_layer.get_inputs_number() == 1, LOG);
}

void ProbabilisticLayerTest::test_get_neurons_number()
{
   cout << "test_get_neurons_number\n";

   ProbabilisticLayer probabilistic_layer;

   // Test 0
   probabilistic_layer.set();
   assert_true(probabilistic_layer.get_neurons_number() == 0, LOG);

   // Test 1
   probabilistic_layer.set_neurons_number(1);
   assert_true(probabilistic_layer.get_neurons_number() == 1, LOG);
}

void ProbabilisticLayerTest::test_get_biases()
{
   cout << "test_get_biases\n";

   ProbabilisticLayer probabilistic_layer;
   Index biases_numb;
   Tensor<type, 2> biases;

   // Test 0
   probabilistic_layer.set();
   probabilistic_layer.set_parameters_constant(0);

   biases_numb = probabilistic_layer.get_biases_number();
   biases = probabilistic_layer.get_biases();

   assert_true(biases_numb == 0, LOG);
   assert_true(biases.size() == 0, LOG);

   // Test 1
   probabilistic_layer.set(1, 1);
   probabilistic_layer.set_parameters_constant(0);

   biases_numb = probabilistic_layer.get_biases_number();
   biases = probabilistic_layer.get_biases();

   assert_true(biases_numb == 1, LOG);
   assert_true(biases.size() == 1, LOG);
   assert_true(biases(0) < numeric_limits<type>::min(), LOG);


   cout << "test_get_biases_with_parameters\n";

   ProbabilisticLayer probabilistic_layer_2;

   // Test  1
   Tensor<type, 2> biases_2(1, 4);
   biases_2.setValues({{9},{8},{7},{6}});

   Tensor<type, 2> synaptic_weights(2, 4);
   synaptic_weights.setValues({{11, 12, 13, 14},{21, 22, 23, 24}});

   Tensor<type, 1> parameters(12);
   probabilistic_layer_2.set(2, 4);

   probabilistic_layer.set_synaptic_weights(synaptic_weights);
   probabilistic_layer_2.set_biases(biases_2);

   parameters = probabilistic_layer_2.get_parameters();
   biases = probabilistic_layer_2.get_biases(parameters);

   assert_true(biases.size() == 4, LOG);
   assert_true(abs(biases(0,0) - 9) < static_cast<type>(1e-5), LOG);
   assert_true(abs(biases(0,3) - 6) < static_cast<type>(1e-5), LOG);
}

void ProbabilisticLayerTest::test_get_synaptic_weights()
{
    cout << "test_get_synaptic_weights\n";

    ProbabilisticLayer probabilistic_layer;
    Tensor<type, 2> synaptic_weights;

    // Test 0
    probabilistic_layer.set(1, 1);

    probabilistic_layer.set_parameters_constant(0.0);

    synaptic_weights = probabilistic_layer.get_synaptic_weights();

    assert_true(synaptic_weights.dimension(0) == 1, LOG);
    assert_true(synaptic_weights.dimension(1) == 1, LOG);
    assert_true(synaptic_weights(0,0) < numeric_limits<type>::min(), LOG);

    cout << "test_get_synaptic_weight_with_parameters\n";

    ProbabilisticLayer probabilistic_layer_2;

    // Test 1
    Tensor<type, 2> biases_2(1, 4);
    biases_2.setValues({{9},{-8},{7},{-6}});

    Tensor<type, 2> synaptic_weights_2(2, 4);
    synaptic_weights_2.setValues({{-11, 12, -13, 14},{21, -22, 23, -24}});

    Tensor<type, 1> parameters(12);
    probabilistic_layer_2.set(2, 4);

    probabilistic_layer_2.set_synaptic_weights(synaptic_weights_2);
    probabilistic_layer_2.set_biases(biases_2);

    parameters = probabilistic_layer_2.get_parameters();
    synaptic_weights_2 = probabilistic_layer_2.get_synaptic_weights(parameters);

    assert_true(synaptic_weights_2.size() == 8, LOG);

    assert_true(abs(synaptic_weights_2(0,0) + 11) < static_cast<type>(1e-5), LOG);
    assert_true(abs(synaptic_weights_2(1,3) + 24) < static_cast<type>(1e-5), LOG);
}

void ProbabilisticLayerTest::test_get_parameters()
{

   cout << "test_get_parameters\n";

   ProbabilisticLayer probabilistic_layer;
   Tensor<type, 2> synaptic_weights;
   Tensor<type, 1> parameters;

   // Test 0
   probabilistic_layer.set(1, 1);
   probabilistic_layer.set_parameters_constant(1.0);

   parameters = probabilistic_layer.get_parameters();

   assert_true(parameters.size() == 2, LOG);
   assert_true(abs(parameters(0) - 1) < numeric_limits<type>::min(), LOG);

   // Test 1
   ProbabilisticLayer probabilistic_layer_2;

   Tensor<type, 2> biases_2(1, 4);
   biases_2.setValues({{9},{-8},{7},{-6}});

   Tensor<type, 2> synaptic_weights_2(2, 4);
   synaptic_weights_2.setValues({{-11, 12, -13, 14},{21, -22, 23, -24}});

   probabilistic_layer_2.set_synaptic_weights(synaptic_weights_2);
   probabilistic_layer_2.set_biases(biases_2);

   Tensor<type,1>new_parameters = probabilistic_layer_2.get_parameters();

   assert_true(new_parameters.size() == 12, LOG);
   assert_true(abs(new_parameters(0) - 9) < static_cast<type>(1e-5), LOG);
   assert_true(abs(new_parameters(4) + 11) < static_cast<type>(1e-5), LOG);
   assert_true(abs(new_parameters(7) + 22) < static_cast<type>(1e-5), LOG);
   }



void ProbabilisticLayerTest::test_set()
{
   cout << "test_set\n";
}

void ProbabilisticLayerTest::test_set_default()
{
   cout << "test_set_default\n";
}

void ProbabilisticLayerTest::test_get_display()
{
   cout << "test_get_display\n";
}

void ProbabilisticLayerTest::test_set_display()
{
   cout << "test_set_display\n";
}





void ProbabilisticLayerTest::test_calculate_outputs()
{
   cout << "test_calculate_outputs\n";
/*
   ProbabilisticLayer probabilistic_layer;

   Tensor<type, 2> inputs(0,0);
   Tensor<type, 2> outputs(0,0);
   Tensor<type, 2> biases(0, 0);
   Tensor<type, 2> synaptic_weights(0,0);

   // Test

   synaptic_weights.resize(1,1);
   synaptic_weights.setConstant(1.0);

   biases.resize(1, 1);
   biases.setConstant(1.0);

//   probabilistic_layer.set_synaptic_weights(synaptic_weights);

   probabilistic_layer.set_neurons_number(1);
   probabilistic_layer.set_synaptic_weights(synaptic_weights);
//   probabilistic_layer.set_biases(biases);

   probabilistic_layer.set_activation_function(ProbabilisticLayer::Binary);

   inputs.resize(1,1);
   inputs.setConstant(0.0);

   outputs = probabilistic_layer.calculate_outputs(inputs);

   assert_true(outputs.size() == 1, LOG);
   assert_true(outputs(0,0) == 0.0, LOG);

   // Test

   probabilistic_layer.set_neurons_number(1);
   probabilistic_layer.set_activation_function(ProbabilisticLayer::Logistic);

   inputs.resize(1,1);
   inputs.setConstant(0.0);
   outputs = probabilistic_layer.calculate_outputs(inputs);

   assert_true(outputs.size() == 1, LOG);
   assert_true(outputs(0) >= 0.0, LOG);*/
}

/*
void ProbabilisticLayerTest::test_to_XML()
{
   cout << "test_to_XML\n";

   ProbabilisticLayer  probabilistic_layer;
   tinyxml2::XMLDocument* pld;

   // Test

   probabilistic_layer.set();

   pld = probabilistic_layer.to_XML();

   assert_true(pld != nullptr, LOG);

   // Test

   probabilistic_layer.set_neurons_number(2);
   probabilistic_layer.set_activation_function(ProbabilisticLayer::Competitive);
   probabilistic_layer.set_display(false);

   pld = probabilistic_layer.to_XML();

   probabilistic_layer.from_XML(*pld);

   assert_true(probabilistic_layer.get_neurons_number() == 2, LOG);
   assert_true(probabilistic_layer.get_activation_function() == ProbabilisticLayer::Competitive, LOG);
   assert_true(probabilistic_layer.get_display() == false, LOG);

   delete pld;
}


void ProbabilisticLayerTest::test_from_XML()
{
   cout << "test_from_XML\n";

   ProbabilisticLayer  probabilistic_layer;
   tinyxml2::XMLDocument* pld;

   // Test

   pld = probabilistic_layer.to_XML();

   probabilistic_layer.from_XML(*pld);

   delete pld;
}
*/

void ProbabilisticLayerTest::test_calculate_activation_derivatives()
{
    cout << "test_calculate_activation_derivatives\n";

    ProbabilisticLayer probabilistic_layer;


    Tensor<type, 1> parameters(1);
    Tensor<type, 2> inputs(1,1);
    Tensor<type, 2> combinations_2d(1,1);
    Tensor<type, 3> activations_derivatives(1,1,1);
    Tensor<type, 2> numerical_activation_derivative;

    Device device(Device::EigenSimpleThreadPool);
    probabilistic_layer.set_device_pointer(&device);

    numerical_differentiation_tests = true;

    // Test 1

    probabilistic_layer.set(1,1);
    probabilistic_layer.set_parameters_constant(1);

    inputs.setConstant(1);

    combinations_2d.setConstant(1);

    activations_derivatives.setZero();

    probabilistic_layer.set_activation_function(ProbabilisticLayer::Logistic);
    probabilistic_layer.calculate_activations_derivatives(combinations_2d,activations_derivatives);


       cout << combinations_2d << endl;
       cout << "------------" << endl;
       cout << activations_derivatives << endl;
       cout << "------------" << endl;
       cout << "------------" << endl;


//       assert_true(abs(derivatives(0,0) - 0.25) < numeric_limits<type>::min(), LOG);

    // Test numerical differentiation

    if(numerical_differentiation_tests)
    {
       probabilistic_layer.set(2, 4);

       combinations_2d.resize(1,4);
       combinations_2d.setConstant(1.0);

       probabilistic_layer.set_activation_function(ProbabilisticLayer::Softmax);

//       activations_derivatives = probabilistic_layer.calculate_activations_derivatives(combinations_2d);

//       numerical_differentiation.calculate_derivatives(probabilistic_layer,
//                                                       &ProbabilisticLayer::calculate_activations,
//                                                       combinations_2d);

//       assert_true((absolute_value(activations_derivatives - numerical_activation_derivative)) < 1.0e-3, LOG);
    }
}


void ProbabilisticLayerTest::run_test_case()
{
   cout << "Running probabilistic layer test case...\n";

   // Constructor and destructor methods

   test_constructor();

   test_destructor();

   // Assignment operators methods

   test_assignment_operator();

   // Get methods

   test_get_biases();
   test_get_synaptic_weights();
   test_get_parameters();

   // Layer architecture

   test_get_inputs_number();
   test_get_neurons_number();

   // Display messages

   test_get_display();

   // Set methods

   test_set();

   test_set_default();

   // Display messages

   test_set_display();

   // Probabilistic post-processing

   test_calculate_outputs();

   // Serialization methods

//   test_to_XML();

//   test_from_XML();

   // Activation derivatives

   test_calculate_activation_derivatives();

   cout << "End of probabilistic layer test case.\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2019 Artificial Intelligence Techniques, SL.
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

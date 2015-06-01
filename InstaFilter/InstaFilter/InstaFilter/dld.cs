using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
//2. 添加所需的命名空間及聲明參數傳遞方式枚舉：
using System.Runtime.InteropServices; // 用 DllImport 需用此 命名空間 
using System.Reflection; // 使用 Assembly 類需用此 命名空間 
using System.Reflection.Emit; // 使用 ILGenerator 需用此 命名空間 

namespace InstaFilter
{
    class dld
    {
        ///  
        /// 參數傳遞方式枚舉 ,ByValue 表示值傳遞 ,ByRef 表示址傳遞 
        ///  
        public enum ModePass
        {
            ByValue = 0x0001,
            ByRef = 0x0002
        }
        //3. 聲明LoadLibrary、GetProcAddress、FreeLibrary及私有變數hModule和farProc：
        ///  
        /// 原型是 :HMODULE LoadLibrary(LPCTSTR lpFileName); 
        ///  
        /// DLL 文件名  
        ///  函數庫模塊的句柄  
        [DllImport("kernel32.dll")]
        static extern IntPtr LoadLibrary(string lpFileName);  ///  
        /// 原型是 : FARPROC GetProcAddress(HMODULE hModule, LPCWSTR lpProcName); 
        ///  
        ///  包含需調用函數的函數庫模塊的句柄  
        ///  調用函數的名稱  
        ///  函數指針  
        [DllImport("kernel32.dll")]
        static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
        ///  
        /// GetProcAddress 返回的函數指針 
        ///  
        private IntPtr _farProc = IntPtr.Zero;
        public IntPtr farProc
        {
            set { _farProc = value; }
            get { return _farProc; }
        }
        ///  
        /// Loadlibrary 返回的函數庫模塊的句柄 
        ///  
        private IntPtr hModule = IntPtr.Zero; ///  
        /// 原型是 : BOOL FreeLibrary(HMODULE hModule); 
        ///  
        ///  需釋放的函數庫模塊的句柄  
        ///  是否已釋放指定的 Dll 
        [DllImport("kernel32.dll", EntryPoint = "FreeLibrary", SetLastError = true)]
        static extern bool FreeLibrary(IntPtr hModule);
        //4.       添加LoadDll方法，並為了調用時方便，重載了這個方法：
        ///  
        /// 裝載 Dll 
        ///  
        /// DLL 文件名  
        public void LoadDll(string lpFileName)
        {
            hModule = LoadLibrary(lpFileName);
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 沒有找到 : " + lpFileName + " ."));
        }
        //若已有已裝載Dll的句柄，可以使用LoadDll方法的第二個版本：
        public void LoadDll(IntPtr HMODULE)
        {
            if (HMODULE == IntPtr.Zero)
                throw (new Exception(" 所傳入的函數庫模塊的句柄 HMODULE 為空 ."));
            hModule = HMODULE;
        }
        //5. 添加LoadFun方法，並為了調用時方便，也重載了這個方法，方法的具體代碼及註釋如下：
        ///  
        /// 獲得函數指針 
        ///  
        ///  調用函數的名稱  
        public void LoadFun(string lpProcName)
        { // 若函數庫模塊的句柄為空，則拋出異常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函數庫模塊的句柄為空 , 請確保已進行 LoadDll 操作 !"));
            // 取得函數指針 
            farProc = GetProcAddress(hModule, lpProcName);
            // 若函數指針，則拋出異常 
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 沒有找到 : " + lpProcName + " 這個函數的入口點 "));
        }
        ///  
        /// 獲得函數指針 
        ///  
        ///  包含需調用函數的 DLL 文件名  
        ///  調用函數的名稱  
        public void LoadFun(string lpFileName, string lpProcName)
        { // 取得函數庫模塊的句柄 
            hModule = LoadLibrary(lpFileName);
            // 若函數庫模塊的句柄為空，則拋出異常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 沒有找到 :" + lpFileName + "."));
            // 取得函數指針 
            farProc = GetProcAddress(hModule, lpProcName);
            // 若函數指針，則拋出異常 
            if (farProc == IntPtr.Zero)
                throw (new Exception("檔案 : " + Path.GetFileName(lpFileName) + " 沒有找到 : " + lpProcName + " 這個函數的入口點 "));
        }
        //6.添加UnLoadDll及Invoke方法，Invoke方法也進行了重載：
        ///  
        /// 卸載 Dll 
        ///  
        public void UnLoadDll()
        {
            FreeLibrary(hModule);
            hModule = IntPtr.Zero;
            farProc = IntPtr.Zero;
        }
        //Invoke方法的第一個版本：
        ///  
        /// 調用所設定的函數 
        ///  
        ///  實參  
        ///  實參類型  
        ///  實參傳送方式  
        ///  返回類型  
        ///  返回所調用函數的 object 
        public object Invoke(object[] ObjArray_Parameter, Type[] TypeArray_ParameterType,
        ModePass[] ModePassArray_Parameter, Type Type_Return)
        {

            // 下面 3 個 if 是進行安全檢查 , 若不能通過 , 則拋出異常
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函數庫模塊的句柄為空 , 請確保已進行 LoadDll 操作 !"));
            if (farProc == IntPtr.Zero)
                throw (new Exception(" 函數指針為空 , 請確保已進行 LoadFun 操作 !"));
            if (ObjArray_Parameter.Length != ModePassArray_Parameter.Length)
                throw (new Exception(" 參數個數及其傳遞方式的個數不匹配 ."));
            // 下面是創建 MyAssemblyName 對象並設置其 Name 屬性 
            AssemblyName MyAssemblyName = new AssemblyName();
            MyAssemblyName.Name = "InvokeFun";
            // 生成單模塊配件
            AssemblyBuilder MyAssemblyBuilder = AppDomain.CurrentDomain.DefineDynamicAssembly(MyAssemblyName, AssemblyBuilderAccess.Run);
            ModuleBuilder MyModuleBuilder = MyAssemblyBuilder.DefineDynamicModule("InvokeDll");
            // 定義要調用的方法 , 方法名為「 MyFun 」，返回類型是「 Type_Return 」參數類型是「 TypeArray_ParameterType 」 
            MethodBuilder MyMethodBuilder = MyModuleBuilder.DefineGlobalMethod("MyFun", MethodAttributes.Public | MethodAttributes.Static, Type_Return, TypeArray_ParameterType);
            // 獲取一個 ILGenerator ，用於發送所需的 IL 
            ILGenerator IL = MyMethodBuilder.GetILGenerator();
            int i;
            for (i = 0; i < ObjArray_Parameter.Length; i++)
            {// 用循环将参数依次压入堆栈
                switch (ModePassArray_Parameter[i])
                {
                    case ModePass.ByValue:
                        IL.Emit(OpCodes.Ldarg, i);
                        break;
                    case ModePass.ByRef:
                        IL.Emit(OpCodes.Ldarga, i);
                        break;
                    default:
                        throw (new Exception(" 第 " + (i + 1).ToString() + " 個參數沒有給定正確的傳遞方式 ."));
                }
            }
            if (IntPtr.Size == 4)
            {// 判断处理器类型
                IL.Emit(OpCodes.Ldc_I4, farProc.ToInt32());
            }
            else if (IntPtr.Size == 8)
            {
                IL.Emit(OpCodes.Ldc_I8, farProc.ToInt64());
            }
            else
            {
                throw new PlatformNotSupportedException();
            }
            IL.EmitCalli(OpCodes.Calli, CallingConvention.StdCall, Type_Return, TypeArray_ParameterType);
            IL.Emit(OpCodes.Ret); // 返回值
            MyModuleBuilder.CreateGlobalFunctions();
            // 取得方法信息
            MethodInfo MyMethodInfo = MyModuleBuilder.GetMethod("MyFun");
            return MyMethodInfo.Invoke(null, ObjArray_Parameter);// 调用方法，并返回其值
        }

        public object Invoke(IntPtr IntPtr_Function, object[] ObjArray_Parameter,
        Type[] TypeArray_ParameterType, ModePass[] ModePassArray_Parameter, Type Type_Return)
        {
            // 下面 2 個 if 是進行安全檢查 , 若不能通過 , 則拋出異常 
            if (hModule == IntPtr.Zero)
                throw (new Exception(" 函數庫模塊的句柄為空 , 請確保已進行 LoadDll 操作 !"));
            if (IntPtr_Function == IntPtr.Zero)
                throw (new Exception(" 函數指針 IntPtr_Function 為空 !"));
            farProc = IntPtr_Function;
            return Invoke(ObjArray_Parameter, TypeArray_ParameterType, ModePassArray_Parameter, Type_Return);
        }

        ~dld()
        {
            this.UnLoadDll();
        }

    }
}